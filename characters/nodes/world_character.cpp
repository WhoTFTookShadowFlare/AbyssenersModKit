#include "core/config/engine.h"

#include "world_character.h"

void WorldCharacter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_character_data", "data"), &WorldCharacter::set_character_data);
	ClassDB::bind_method(D_METHOD("get_character_data"), &WorldCharacter::get_character_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "data", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE),
		"set_character_data", "get_character_data"
	);

	ClassDB::bind_method(D_METHOD("get_damage_handler_queue"), &WorldCharacter::get_damage_handler_queue);
	ClassDB::bind_method(D_METHOD("handle_damage", "source"), &WorldCharacter::handle_damage);

	ClassDB::bind_method(D_METHOD("_set_is_dead", "value"), &WorldCharacter::set_is_dead);
	ClassDB::bind_method(D_METHOD("get_is_dead"), &WorldCharacter::get_is_dead);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_dead"), "_set_is_dead", "get_is_dead");

	ADD_SIGNAL(MethodInfo("on_death"));
	ADD_SIGNAL(MethodInfo("on_revive"));

	ClassDB::bind_method(D_METHOD("add_component", "instance_str"), &WorldCharacter::add_component);
	ClassDB::bind_method(D_METHOD("has_component", "type"), &WorldCharacter::has_component);
	ClassDB::bind_method(D_METHOD("get_component", "type"), &WorldCharacter::get_component);

	ClassDB::bind_method(D_METHOD("_set_additive_stat_modifiers", "modifiers"), &WorldCharacter::set_additive_stat_modifiers);
	ClassDB::bind_method(D_METHOD("get_additive_stat_modifiers"), &WorldCharacter::get_additive_stat_modifiers);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "additive_stat_modifiers"), "_set_additive_stat_modifiers", "get_additive_stat_modifiers");

	ClassDB::bind_method(D_METHOD("_set_multiplicitive_stat_modifiers", "modifiers"), &WorldCharacter::set_multiplicitive_stat_modifiers);
	ClassDB::bind_method(D_METHOD("get_multiplicitive_stat_modifiers"), &WorldCharacter::get_multiplicitive_stat_modifiers);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "multiplicitive_modifiers"), "_set_multiplicitive_stat_modifiers", "get_multiplicitive_stat_modifiers");

	ClassDB::bind_method(D_METHOD("can_have_stat_modifier", "modifier"), &WorldCharacter::can_have_stat_modifier);
	ClassDB::bind_method(D_METHOD("add_stat_modifier", "modifier"), &WorldCharacter::add_stat_modifier);
	ClassDB::bind_method(D_METHOD("remove_stat_modifier", "modifier"), &WorldCharacter::remove_stat_modifier);
}

WorldCharacter::WorldCharacter() {}

void WorldCharacter::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_READY: {
		set_physics_process_internal(true);

		connect("on_death", Callable(this, "_set_is_dead").bind(true));
		connect("on_revive", Callable(this, "_set_is_dead").bind(false));
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		Vector3 velo = get_velocity();
		velo.x /= 1.2;
		velo.z /= 1.2;
		set_velocity(velo);
		move_and_slide();

		if(data->get_rotates_to_velocity()) {
			Vector3 look_target = get_position() + velo;
			look_target.y = get_position().y;
			if(!get_position().is_equal_approx(look_target)) look_at(look_target);
		}
	}; break;
	default:
		break;
	}
}

void WorldCharacter::set_is_dead(bool value) {
	is_dead = value;
}

bool WorldCharacter::get_is_dead() {
	return is_dead;
}

void WorldCharacter::set_character_data(Ref<CharacterData> data_ref) {
	ERR_FAIL_COND_MSG(this->data.is_valid() && !Engine::get_singleton()->is_editor_hint(), "A character already has data set");
	this->data = data_ref;
}

Ref<CharacterData> WorldCharacter::get_character_data() {
	return this->data;
}

TypedArray<Callable> WorldCharacter::get_damage_handler_queue() {
	return damage_handler_queue;
}

void WorldCharacter::handle_damage(Ref<DamageSource> src) {
	if(src.is_null()) return;

	print_verbose("damaging " + get_name() + ":");
	for(int c_idx = 0; c_idx < damage_handler_queue.size(); c_idx++) {
		Callable func = damage_handler_queue[c_idx];
		print_verbose("\t" + func);
		func.call(src);
		if(src->get_amount() == 0) break;
	}

	if(src->get_amount() > 0) emit_signal("on_death");
}

Node *WorldCharacter::add_component(String instance_str) {
	String comp_id = instance_str.substr(0, instance_str.find(":"));
	ERR_FAIL_COND_V_MSG(!ClassDB::can_instantiate, nullptr, "Cannot instance " + comp_id);

	Object *obj = ClassDB::instantiate(comp_id);
	if(!obj->is_class(Node::get_class_static())) {
		memfree(obj);
		ERR_FAIL_V_MSG(nullptr, comp_id + " was not a Node");
	}

	Node *comp = cast_to<Node>(obj);
	add_child(comp);
	comp->set_owner(this);

	if(instance_str.contains(":")) {
		String prop_changes = instance_str.substr(instance_str.find(":") + 1);
		PackedStringArray properties = prop_changes.split(",");
		for(String property_entry : properties) {
			ERR_CONTINUE(!property_entry.contains("="));
			String property_name = property_entry.substr(0, property_entry.find("="));
			String property_value = property_entry.substr(property_entry.find("=") + 1);

			comp->set(property_name, property_value);
		}
	}

	return comp;
}

bool WorldCharacter::has_component(String type) {
	return get_component(type);
}

Node *WorldCharacter::get_component(String type) {
	for(Variant child_var : get_children()) {
		Node *child = cast_to<Node>(child_var.operator Object *());
		if(child->get_class() == type) {
			return child;
		}
	}

	return nullptr;
}

bool WorldCharacter::can_have_stat_modifier(Ref<StatModifier> modifier) {
	if(modifier.is_null()) return false;

	Node *component = get_component(modifier->get_target_component());
	if(component == nullptr) {
		return false;
	}

	List<PropertyInfo> properties;
	component->get_property_list(&properties);
	for(PropertyInfo property : properties) {
		if(property.name == modifier->get_target_property()) {
			return true;
		}
	}

	return false;
}

void WorldCharacter::apply_stat_modifier(Ref<StatModifier> modifier) {
	Node *comp = get_component(modifier->get_target_component());
	if(modifier->is_multiplicitive()) {
		comp->set(modifier->get_target_property(), comp->get(modifier->get_target_property()).operator double() * modifier->get_change());
	} else {
		double mul_amount = 0.0;
		for(Variant var : multiplicitive_stat_modifiers) {
			if(var.get_type() != Variant::OBJECT) continue;
			Object *obj = var.operator Object *();
			if(!obj->is_class(StatModifier::get_class_static())) continue;
			StatModifier *existing_modifier = cast_to<StatModifier>(obj);
			mul_amount += existing_modifier->get_change();
		}
		comp->set(modifier->get_target_property(), comp->get(modifier->get_target_property()).operator double() + (modifier->get_change() * mul_amount));
	}
}

void WorldCharacter::unapply_stat_modifier(Ref<StatModifier> modifier) {
	Node *comp = get_component(modifier->get_target_component());
	if(modifier->is_multiplicitive()) {
		comp->set(modifier->get_target_property(), comp->get(modifier->get_target_property()).operator double() / modifier->get_change());
	} else {
		double mul_amount = 0.0;
		for(Variant var : multiplicitive_stat_modifiers) {
			if(var.get_type() != Variant::OBJECT) continue;
			Object *obj = var.operator Object *();
			if(!obj->is_class(StatModifier::get_class_static())) continue;
			StatModifier *existing_modifier = cast_to<StatModifier>(obj);
			mul_amount += existing_modifier->get_change();
		}
		comp->set(modifier->get_target_property(), comp->get(modifier->get_target_property()).operator double() - (modifier->get_change() * mul_amount));
	}
}

void WorldCharacter::add_stat_modifier(Ref<StatModifier> modifier) {
	if(!can_have_stat_modifier(modifier)) return;
	if(modifier->is_multiplicitive()) {
		multiplicitive_stat_modifiers.append(modifier);
	} else {
		additive_stat_modifiers.append(modifier);
	}
	apply_stat_modifier(modifier);
}

void WorldCharacter::remove_stat_modifier(Ref<StatModifier> modifier) {
	TypedArray<StatModifier> from;
	if(modifier->is_multiplicitive()) from = multiplicitive_stat_modifiers;
	else from = additive_stat_modifiers;
	for(Variant applied_var : from) {
		if(applied_var.get_type() != Variant::OBJECT) continue;
		Object *applied_obj = applied_var.operator Object *();
		if(!applied_obj->is_class(StatModifier::get_class_static())) continue;
		StatModifier *applied = cast_to<StatModifier>(applied_obj);
		if(!modifier->equals(applied)) continue;
		unapply_stat_modifier(applied);
		from.erase(applied);
		break;
	}
}

void WorldCharacter::set_additive_stat_modifiers(TypedArray<StatModifier> modifiers) {
	if(additive_stat_modifiers.is_empty()) additive_stat_modifiers = modifiers;
}

TypedArray<StatModifier> WorldCharacter::get_additive_stat_modifiers() {
	return additive_stat_modifiers.duplicate();
}

void WorldCharacter::set_multiplicitive_stat_modifiers(TypedArray<StatModifier> modifiers) {
	if(multiplicitive_stat_modifiers.is_empty()) multiplicitive_stat_modifiers = modifiers;
}

TypedArray<StatModifier> WorldCharacter::get_multiplicitive_stat_modifiers() {
	return multiplicitive_stat_modifiers.duplicate();
}
