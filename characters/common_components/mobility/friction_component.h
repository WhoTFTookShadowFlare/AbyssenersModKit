#ifndef FRICTION_COMPONENT_H
#define FRICTION_COMPONENT_H

#include "scene/main/node.h"

#include "../../world_character.h"

class FrictionComponent final : public Node {
	GDCLASS(FrictionComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	double friction = 1.2;
	double air_resistance = 1.125;

	WorldCharacter *character;

public:
	FrictionComponent();

	double get_friction();
	void set_friction(double value);

	double get_air_resistance();
	void set_air_resistance(double value);
};

#endif // FRICTION_COMPONENT_H