#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "scene/3d/navigation_agent_3d.h"
#include "servers/navigation_server_3d.h"

#include "../../world_character.h"

class PathingComponent : public NavigationAgent3D {
	GDCLASS(PathingComponent, NavigationAgent3D);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	WorldCharacter *character;

	double speed = 1.0;
public:
	PathingComponent();

	void set_speed(double value);
	double get_speed();
};

#endif // MOVEMENT_COMPONENT_H