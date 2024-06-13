#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "scene/3d/physics/collision_shape_3d.h"

class CollisionComponent : public CollisionShape3D {
	GDCLASS(CollisionComponent, CollisionShape3D);
protected:
	static void _bind_methods();
	void _notification(int p_what);
public:
	CollisionComponent();
};

#endif // COLLISION_COMPONENT_H