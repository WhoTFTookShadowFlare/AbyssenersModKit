#include "health_component.h"

#include "../../world_character.h"

#include <string>

HealthComponent::HealthComponent() {}

void HealthComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_health", "value"), &HealthComponent::set_health);
	ClassDB::bind_method(D_METHOD("get_health"), &HealthComponent::get_health);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "health"), "set_health", "get_health");

	ClassDB::bind_method(D_METHOD("set_max_health", "value"), &HealthComponent::set_max_health);
	ClassDB::bind_method(D_METHOD("get_max_health"), &HealthComponent::get_max_health);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_health"), "set_max_health", "get_max_health");

	ClassDB::bind_method(D_METHOD("heal", "amount"), &HealthComponent::heal);
	ClassDB::bind_method(D_METHOD("damage", "amount"), &HealthComponent::damage);

	ClassDB::bind_method(D_METHOD("get_health_string"), &HealthComponent::get_health_string);
	ClassDB::bind_method(D_METHOD("get_max_health_string"), &HealthComponent::get_max_health_string);

	ClassDB::bind_method(D_METHOD("get_health_pct"), &HealthComponent::get_health_pct);

	ClassDB::bind_method(D_METHOD("set_regen", "value"), &HealthComponent::set_regen);
	ClassDB::bind_method(D_METHOD("get_regen"), &HealthComponent::get_regen);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "regen"), "set_regen", "get_regen");

	ClassDB::bind_method(D_METHOD("set_time_per_heal", "value"), &HealthComponent::set_time_per_heal);
	ClassDB::bind_method(D_METHOD("get_time_per_heal"), &HealthComponent::get_time_per_heal);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time_per_heal"), "set_time_per_heal", "get_time_per_heal");

	ClassDB::bind_method(D_METHOD("set_next_heal_time", "value"), &HealthComponent::set_next_heal_time);
	ClassDB::bind_method(D_METHOD("get_next_heal_time"), &HealthComponent::get_next_heal_time);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "next_heal_time"), "set_next_heal_time", "get_next_heal_time");

	ADD_SIGNAL(MethodInfo("on_heal", PropertyInfo(Variant::INT, "amount")));
	ADD_SIGNAL(MethodInfo("on_damage", PropertyInfo(Variant::INT, "amount")));

	ClassDB::bind_method(D_METHOD("handle_damage", "source"), &HealthComponent::handle_damage);
}

void HealthComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;
	
	switch(p_what) {
	case NOTIFICATION_READY: {
		set_physics_process_internal(true);
		
		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		character = cast_to<WorldCharacter>(parent);
		TypedArray<Callable> damage_handler = character->get_damage_handler_queue();
		damage_handler.push_back(Callable(this, "handle_damage"));
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		if(!character) break;
		if(character->get_is_dead()) break;
		
		double delta = get_physics_process_delta_time();
		set_next_heal_time(get_next_heal_time() - delta);
		if(get_time_per_heal() > 0.0)
			while(get_next_heal_time() <= 0.0) {
				set_next_heal_time(get_next_heal_time() + get_time_per_heal());
				heal(get_regen());
			}
		else {
			heal(get_max_health());
		}
	} break;
	default:
		break;
	}
}

void HealthComponent::handle_damage(Ref<DamageSource> source) {

}

void HealthComponent::set_health(u_int64_t value) {
	health = value;
	if(health > max_health) health = max_health;
}

u_int64_t HealthComponent::get_health() {
	return health;
}

void HealthComponent::set_max_health(u_int64_t value) {
	max_health = value;
	set_health(get_health());
}

u_int64_t HealthComponent::get_max_health() {
	return max_health;
}

u_int64_t HealthComponent::get_regen() {
	return regen;
}

void HealthComponent::set_regen(u_int64_t value) {
	regen = value;
	if(regen == 0) regen = 1;
}

double HealthComponent::get_time_per_heal() {
	return time_per_heal;
}

void HealthComponent::set_time_per_heal(double value) {
	time_per_heal = value;
}

double HealthComponent::get_next_heal_time() {
	return next_heal_time;
}

void HealthComponent::set_next_heal_time(double value) {
	next_heal_time = value;
}

void HealthComponent::heal(u_int64_t amount) {
	ERR_FAIL_COND(!character);
	if(get_health() > std::numeric_limits<u_int64_t>::max() + get_health() + amount)
		set_health(std::numeric_limits<u_int64_t>::max());
	else
		set_health(get_health() + amount);
	if(character->get_is_dead() && get_health() > 0) character->emit_signal("on_revive");
	emit_signal("on_heal", amount);
}

void HealthComponent::damage(u_int64_t amount) {
	ERR_FAIL_COND(!character);
	if(character->get_is_dead()) return;
	if(get_health() < std::numeric_limits<u_int64_t>::min() - get_health() - amount)
		set_health(0);
	else
		set_health(get_health() - amount);
	emit_signal("on_damage", amount);
}

double HealthComponent::get_health_pct() {
	return ((double) get_health()) / ((double) get_max_health());
}

String HealthComponent::get_health_string() {
	return std::to_string(health).c_str();
}

String HealthComponent::get_max_health_string() {
	return std::to_string(max_health).c_str();
}