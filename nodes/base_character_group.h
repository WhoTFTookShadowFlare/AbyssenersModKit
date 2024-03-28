#ifndef BASE_CHARACTER_GROUP_H
#define BASE_CHARACTER_GROUP_H

#include "scene/main/node.h"

#include "core/string/ustring.h"
#include "../characters/world_character.h"
#include "../resources/save_file.h"

class BaseCharacterGroup : public Node {
	GDCLASS(BaseCharacterGroup, Node);
protected:
	static void _bind_methods();

public:
	BaseCharacterGroup();

	WorldCharacter *try_spawn_character(String character_name);

	void save_characters(SaveFile *file);
	void load_characters(SaveFile *file);
};

#endif // BASE_CHARACTER_GROUP_H