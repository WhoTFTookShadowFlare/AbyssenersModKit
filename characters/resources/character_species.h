#ifndef CHARACTER_SPECIES_H
#define CHARACTER_SPECIES_H

#include "core/io/resource.h"
#include "core/string/ustring.h"

class CharacterSpecies : public Resource {
	GDCLASS(CharacterSpecies, Resource);
protected:
	static void _bind_methods();

	String sprites_dir;
public:
	CharacterSpecies();

	void set_sprites_dir(String value);
	String get_sprites_dir();
};

#endif // CHARACTER_SPECIES_H