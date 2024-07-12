#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "scene/main/node.h"

#include "../../characters/nodes/world_character.h"

#include "projectile.h"

class ProjectileManager : public Node { 
	GDCLASS(ProjectileManager, Node);
protected:
	static void _bind_methods();
	static ProjectileManager *singleton;			
	void _setup();

public:
	static ProjectileManager *get_singleton();
	ProjectileManager();

	Projectile *spawn_projectile();
	Projectile *spawn_projectile_for(WorldCharacter *character);
};

#endif // PROJECTILE_MANAGER_H