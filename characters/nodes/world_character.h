#ifndef WORLD_CHARACTER_H
#define WORLD_CHARACTER_H

#include "scene/3d/physics/character_body_3d.h"

#include "../resources/character_data.h"
#include "../resources/damage_source.h"
#include "../resources/stat_modifier.h"

class WorldCharacter final : public CharacterBody3D {
	GDCLASS(WorldCharacter, CharacterBody3D);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	Ref<CharacterData> data;
	TypedArray<Callable> damage_handler_queue;

	bool is_dead = false;
	void set_is_dead(bool value);

	TypedArray<StatModifier> additive_stat_modifiers;
	TypedArray<StatModifier> multiplicitive_stat_modifiers; // Applied after additive

	void apply_stat_modifier(Ref<StatModifier> modifier);
	void unapply_stat_modifier(Ref<StatModifier> modifier);

	void set_additive_stat_modifiers(TypedArray<StatModifier> modifiers);
	void set_multiplicitive_stat_modifiers(TypedArray<StatModifier> modifiers);
public:
	WorldCharacter();

	bool get_is_dead();

	void set_character_data(Ref<CharacterData> data_ref);
	Ref<CharacterData> get_character_data();

	TypedArray<Callable> get_damage_handler_queue();
	void handle_damage(Ref<DamageSource> source);

	Node *get_component(String type);

	bool can_have_stat_modifier(Ref<StatModifier> modifier);

	void add_stat_modifier(Ref<StatModifier> modifier);
	void remove_stat_modifier(Ref<StatModifier> modifier);

	TypedArray<StatModifier> get_additive_stat_modifiers();
	TypedArray<StatModifier> get_multiplicitive_stat_modifiers();
};

#endif // WORLD_CHARACTER_H
