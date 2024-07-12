#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "scene/3d/physics/area_3d.h"

#include "../../characters/resources/damage_source.h"

class Projectile : public Area3D {
	GDCLASS(Projectile, Area3D);
protected:
	static void _bind_methods();

	Ref<DamageSource> damage;
public:
	Projectile();

	void set_damage_source(Ref<DamageSource> value);
	Ref<DamageSource> get_damage_source();
};

#endif // PROJECTILE_H