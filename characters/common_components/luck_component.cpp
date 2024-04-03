#include "luck_component.h"

LuckComponent::LuckComponent() {}

void LuckComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_luck"), &LuckComponent::get_luck);
	ClassDB::bind_method(D_METHOD("set_luck", "luck"), &LuckComponent::set_luck);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "luck"), "set_luck", "get_luck");

	ClassDB::bind_method(D_METHOD("get_rand_float", "luck_impact"), &LuckComponent::get_rand_float);
	ClassDB::bind_method(D_METHOD("get_rand_int", "luck_impact"), &LuckComponent::get_rand_int);
	ClassDB::bind_method(D_METHOD("get_rand_bool", "luck_impact"), &LuckComponent::get_rand_bool);
}

void LuckComponent::set_luck(real_t value) {
	luck = value;
}

real_t LuckComponent::get_luck() {
	return luck;
}

real_t LuckComponent::get_rand_float(real_t luck_impact) {
	return CLAMP(rng.randf_range(0.0, 1.0) + (luck * abs(luck_impact)), 0.0, 1.0);
}

int64_t LuckComponent::get_rand_int(real_t luck_impact) {
	return rng.randi() + round(luck * abs(luck_impact));
}

bool LuckComponent::get_rand_bool(real_t luck_impact) {
	return get_rand_float(luck_impact) >= 0.5;
}