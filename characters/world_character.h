#ifndef WORLD_CHARACTER_H
#define WORLD_CHARACTER_H

#include "scene/2d/physics_body_2d.h"

#include "character_data.h"
#include "../resources/damage_source.h"

class WorldCharacter final : public CharacterBody2D {
	GDCLASS(WorldCharacter, CharacterBody2D);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	Ref<CharacterData> data;
	TypedArray<Callable> damage_handler_queue;

	bool is_dead = false;
	void set_is_dead(bool value);

public:
	WorldCharacter();

	bool get_is_dead();

	void set_character_data(Ref<CharacterData> data_ref);
	Ref<CharacterData> get_character_data();

	TypedArray<Callable> get_damage_handler_queue();
	void handle_damage(Ref<DamageSource> source);
};

#endif // WORLD_CHARACTER_H
