#ifndef CHARACTER_SPECIES_H
#define CHARACTER_SPECIES_H

#include "core/io/resource.h"
#include "core/string/ustring.h"
#include "core/variant/typed_array.h"
#include "scene/resources/sprite_frames.h"

#include "stat_modifier.h"
#include "../../resources/base_item.h"

class CharacterSpecies : public Resource {
	GDCLASS(CharacterSpecies, Resource);
protected:
	static void _bind_methods();

	String anims_dir;
	Ref<SpriteFrames> animation_data;

	TypedArray<StatModifier> default_stat_modifiers;

	Ref<BaseItem> default_weapon;
public:
	CharacterSpecies();

	void set_animations_dir(String value);
	String get_animations_dir();

	void set_default_stat_modifiers(TypedArray<StatModifier> value);
	TypedArray<StatModifier> get_default_stat_modifiers();

	Ref<SpriteFrames> get_animation_data();

	void set_default_weapon(Ref<BaseItem> item);
	Ref<BaseItem> get_default_weapon();
};

#endif // CHARACTER_SPECIES_H