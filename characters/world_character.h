#ifndef WORLD_CHARACTER_H
#define WORLD_CHARACTER_H

#include "scene/2d/physics_body_2d.h"

#include "character_data.h"

class WorldCharacter final : public CharacterBody2D {
	GDCLASS(WorldCharacter, CharacterBody2D);

protected:
	static void _bind_methods();

	Ref<CharacterData> data;

public:
	WorldCharacter();

	void set_character_data(Ref<CharacterData> data_ref);
	Ref<CharacterData> get_character_data();
};

#endif // WORLD_CHARACTER_H
