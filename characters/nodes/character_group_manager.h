#ifndef CHARACTER_GROUP_MANAGER_H
#define CHARACTER_GROUP_MANAGER_H

#include "scene/main/node.h"

#include "base_character_group.h"

class CharacterGroupManager final : public Node {
	GDCLASS(CharacterGroupManager, Node);
protected:
	static void _bind_methods();
	static CharacterGroupManager *singleton;
	void _setup();
public:
	static CharacterGroupManager *get_singleton();
	CharacterGroupManager();

	void add_group(BaseCharacterGroup *group);
	BaseCharacterGroup *get_group(String name);
	bool has_group(String name);
};

#endif // CHARACTER_GROUP_MANAGER_H