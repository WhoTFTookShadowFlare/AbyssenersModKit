#ifndef GRAVITY_COMPONENT_H
#define GRAVITY_COMPONENT_H

#include "scene/main/node.h"

#include "../../world_character.h"

class GravityComponent final : public Node {
	GDCLASS(GravityComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	WorldCharacter *character;

	double gravity = 9.8;

public:
	GravityComponent();

	void set_gravity(double value);
	double get_gravity();
};

#endif // GRAVITY_COMPONENT_H