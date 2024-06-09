#include "armor_component.h"

#include "core/math/math_funcs.h"

#include "../../world_character.h"

ArmorComponent::ArmorComponent() {}

void ArmorComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_armor", "value"), &ArmorComponent::set_armor);
	ClassDB::bind_method(D_METHOD("get_armor"), &ArmorComponent::get_armor);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "armor"), "set_armor", "get_armor");

	ClassDB::bind_method(D_METHOD("set_max_armor", "value"), &ArmorComponent::set_max_armor);
	ClassDB::bind_method(D_METHOD("get_max_armor"), &ArmorComponent::get_max_armor);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_armor"), "set_max_armor", "get_max_armor");

	ClassDB::bind_method(D_METHOD("set_gen_hit_delay", "value"), &ArmorComponent::set_gen_hit_delay);
	ClassDB::bind_method(D_METHOD("get_gen_hit_delay"), &ArmorComponent::get_gen_hit_delay);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gen_hit_delay"), "set_gen_hit_delay", "get_gen_hit_delay");

	ClassDB::bind_method(D_METHOD("set_gen_tick_rate", "value"), &ArmorComponent::set_gen_tick_rate);
	ClassDB::bind_method(D_METHOD("get_gen_tick_rate"), &ArmorComponent::get_gen_tick_rate);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gen_tick_rate"), "set_gen_tick_rate", "get_gen_tick_rate");

	ClassDB::bind_method(D_METHOD("set_next_gen_tick", "value"), &ArmorComponent::set_next_gen_tick);
	ClassDB::bind_method(D_METHOD("get_next_gen_tick"), &ArmorComponent::get_next_gen_tick);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "next_gen_tick"), "set_next_gen_tick", "get_next_gen_tick");

	ClassDB::bind_method(D_METHOD("set_generated_pct", "value"), &ArmorComponent::set_generated_pct);
	ClassDB::bind_method(D_METHOD("get_generated_pct"), &ArmorComponent::get_generated_pct);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "generated_pct"), "set_generated_pct", "get_generated_pct");

	ClassDB::bind_method(D_METHOD("set_armor_effeciency", "value"), &ArmorComponent::set_armor_effeciency);
	ClassDB::bind_method(D_METHOD("get_armor_effeciency"), &ArmorComponent::get_armor_effeciency);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "armor_effeciency"), "set_armor_effeciency", "get_armor_effeciency");

	ClassDB::bind_method(D_METHOD("get_armor_pct"), &ArmorComponent::get_armor_pct);
	ClassDB::bind_method(D_METHOD("get_tank_pct"), &ArmorComponent::get_tank_pct);

	ClassDB::bind_method(D_METHOD("repair", "amount"), &ArmorComponent::repair);
	ClassDB::bind_method(D_METHOD("damage", "amount"), &ArmorComponent::damage);
	
	ADD_SIGNAL(MethodInfo("armor_break"));
	ADD_SIGNAL(MethodInfo("armor_repaired", PropertyInfo(Variant::FLOAT, "amount")));
	ADD_SIGNAL(MethodInfo("armor_damaged", PropertyInfo(Variant::FLOAT, "amount")));

	ClassDB::bind_method(D_METHOD("handle_damage", "source"), &ArmorComponent::handle_damage);
}

void ArmorComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_PARENTED: {
		set_physics_process_internal(true);

		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		character = cast_to<WorldCharacter>(parent);

		TypedArray<Callable> damage_handler = character->get_damage_handler_queue();
		damage_handler.push_front(Callable(this, "handle_damage"));
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		if(character->get_is_dead()) return;

		double delta = get_physics_process_delta_time();
		set_next_gen_tick(get_next_gen_tick() - delta);
		if(gen_tick_rate > 0.0)
			while(next_gen_tick <= 0.0) {
				next_gen_tick += gen_tick_rate;
				double amount = ceil(((double) max_armor) * gen_pct);
				repair(amount);
			}
		else {
			armor = max_armor;
		}
	} break;
	default:
		break;
	}
}

void ArmorComponent::handle_damage(Ref<DamageSource> source) {
	if(source.is_null()) return;
	if(source->has_flag(ArmorComponent::ARMOR_PRIERCE_FLAG)) return;

	double tanked = round(get_tank_pct() * source->get_amount());
	armor -= tanked;
	source->set_amount(source->get_amount() - tanked);
	if(armor <= 0) {
		tanked = abs(armor);
		armor = 0;
		source->set_amount(source->get_amount() + tanked);
	}
}

void ArmorComponent::set_armor(double value) {
	armor = value;
	if(armor > max_armor) armor = max_armor;
}

double ArmorComponent::get_armor() {
	return armor;
}

void ArmorComponent::set_max_armor(double value) {
	double armor_pct = get_armor_pct();
	max_armor = value;
	set_armor(max_armor * armor_pct);
}

double ArmorComponent::get_max_armor() {
	return max_armor;
}

double ArmorComponent::get_armor_pct() {
	return ((double) get_armor()) / ((double) get_max_armor());
}

double ArmorComponent::get_tank_pct() {
	return get_armor_pct() * get_armor_effeciency();
}

void ArmorComponent::repair(double amount) {
	set_armor(amount + armor);
	emit_signal("armor_repaired", amount);
}

void ArmorComponent::damage(double amount) {
	set_armor(armor - amount);
	emit_signal("armor_damaged", amount);
}

void ArmorComponent::set_gen_hit_delay(double value) {
	gen_hit_delay = value;
}

double ArmorComponent::get_gen_hit_delay() {
	return gen_hit_delay;
}

void ArmorComponent::set_gen_tick_rate(double value) {
	gen_tick_rate = value;
}

double ArmorComponent::get_gen_tick_rate() {
	return gen_tick_rate;
}

void ArmorComponent::set_next_gen_tick(double value) {
	next_gen_tick = value;
}

double ArmorComponent::get_next_gen_tick() {
	return next_gen_tick;
}

void ArmorComponent::set_generated_pct(double value) {
	gen_pct = CLAMP(value, 0.0, 1.0);
}

double ArmorComponent::get_generated_pct() {
	return gen_pct;
}

void ArmorComponent::set_armor_effeciency(double value) {
	armor_effeciency = CLAMP(value, 0.0, 1.0);
}

double ArmorComponent::get_armor_effeciency() {
	return armor_effeciency;
}