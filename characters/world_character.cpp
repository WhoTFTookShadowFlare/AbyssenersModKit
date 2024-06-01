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

	ClassDB::bind_method(D_METHOD("get_component", "type"), &WorldCharacter::get_component);
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
	print_verbose("damaging " + get_name() + ":");
	for(int c_idx = 0; c_idx < damage_handler_queue.size(); c_idx++) {
		Callable func = damage_handler_queue[c_idx];
		print_verbose("\t" + func);
		func.call(src);
		if(src->get_amount() == 0) break;
	}

	if(src->get_amount() > 0) emit_signal("on_death");
}

Node *WorldCharacter::get_component(StringName type) {
	for(Variant child_var : get_children()) {
		Node *child = cast_to<Node>(child_var.operator Object *());
		if(child->get_class() == type) {
			return child;
		}
	}

	return nullptr;
}