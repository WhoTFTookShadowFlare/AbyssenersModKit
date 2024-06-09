#include "health_component.h"

#include "../../world_character.h"

#include <string>

HealthComponent::HealthComponent() {}

void HealthComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_health", "value"), &HealthComponent::set_health);
	ClassDB::bind_method(D_METHOD("get_health"), &HealthComponent::get_health);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "health"), "set_health", "get_health");

	ClassDB::bind_method(D_METHOD("set_max_health", "value"), &HealthComponent::set_max_health);
	ClassDB::bind_method(D_METHOD("get_max_health"), &HealthComponent::get_max_health);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_health"), "set_max_health", "get_max_health");

	ClassDB::bind_method(D_METHOD("heal", "amount"), &HealthComponent::heal);
	ClassDB::bind_method(D_METHOD("damage", "amount"), &HealthComponent::damage);

	ClassDB::bind_method(D_METHOD("get_health_pct"), &HealthComponent::get_health_pct);

	ADD_SIGNAL(MethodInfo("on_heal", PropertyInfo(Variant::FLOAT, "amount")));
	ADD_SIGNAL(MethodInfo("on_damage", PropertyInfo(Variant::FLOAT, "amount")));

	ClassDB::bind_method(D_METHOD("handle_damage", "source"), &HealthComponent::handle_damage);
}

void HealthComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;
	
	switch(p_what) {
	case NOTIFICATION_PARENTED: {
		set_physics_process_internal(true);
		
		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		character = cast_to<WorldCharacter>(parent);
		TypedArray<Callable> damage_handler = character->get_damage_handler_queue();
		damage_handler.push_back(Callable(this, "handle_damage"));
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		
	} break;
	default:
		break;
	}
}

void HealthComponent::handle_damage(Ref<DamageSource> source) {
	if(source.is_null()) return;

	health -= source->get_amount();
	source->set_amount(abs(health));
	if(health < 0) health = 0;
}

void HealthComponent::set_health(double value) {
	health = value;
	if(health > max_health) health = max_health;
}

double HealthComponent::get_health() {
	return health;
}

void HealthComponent::set_max_health(double value) {
	double health_pct = get_health_pct();
	max_health = value;
	set_health(max_health * health_pct);
}

double HealthComponent::get_max_health() {
	return max_health;
}

void HealthComponent::heal(double amount) {
	ERR_FAIL_COND(!character);
	if(get_health() > std::numeric_limits<double>::max() + get_health() + amount)
		set_health(std::numeric_limits<double>::max());
	else
		set_health(get_health() + amount);
	if(character->get_is_dead() && get_health() > 0) character->emit_signal("on_revive");
	emit_signal("on_heal", amount);
}

void HealthComponent::damage(double amount) {
	ERR_FAIL_COND(!character);
	if(character->get_is_dead()) return;
	if(get_health() < std::numeric_limits<double>::min() - get_health() - amount)
		set_health(0);
	else
		set_health(get_health() - amount);
	emit_signal("on_damage", amount);
}

double HealthComponent::get_health_pct() {
	return ((double) get_health()) / ((double) get_max_health());
}