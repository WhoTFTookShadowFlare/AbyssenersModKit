#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "scene/2d/navigation_agent_2d.h"
#include "servers/navigation_server_2d.h"

#include "../../world_character.h"

class MovementComponent : public NavigationAgent2D {
	GDCLASS(MovementComponent, NavigationAgent2D);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	WorldCharacter *character;

	double speed = 1.0;
public:
	MovementComponent();

	void set_speed(double value);
	double get_speed();
};

#endif // MOVEMENT_COMPONENT_H