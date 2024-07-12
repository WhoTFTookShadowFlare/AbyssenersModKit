#include "projectile.h"

Projectile::Projectile() {}

void Projectile::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_damage_source", "value"), &Projectile::set_damage_source);
	ClassDB::bind_method(D_METHOD("get_damage_source"), &Projectile::get_damage_source);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::OBJECT, "damage_source",
			PROPERTY_HINT_RESOURCE_TYPE, DamageSource::get_class_static()
		),
		"set_damage_source", "get_damage_source"
	);
}

void Projectile::set_damage_source(Ref<DamageSource> value) {
	damage = value;
}

Ref<DamageSource> Projectile::get_damage_source() {
	return damage;
}