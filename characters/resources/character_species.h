#ifndef CHARACTER_SPECIES_H
#define CHARACTER_SPECIES_H

#include "core/io/resource.h"
#include "core/string/ustring.h"
#include "core/variant/typed_array.h"

#include "stat_modifier.h"

class CharacterSpecies : public Resource {
	GDCLASS(CharacterSpecies, Resource);
protected:
	static void _bind_methods();

	String sprites_dir;

	TypedArray<StatModifier> default_stat_modifiers;
public:
	CharacterSpecies();

	void set_sprites_dir(String value);
	String get_sprites_dir();

	void set_default_stat_modifiers(TypedArray<StatModifier> value);
	TypedArray<StatModifier> get_default_stat_modifiers();
};

#endif // CHARACTER_SPECIES_H