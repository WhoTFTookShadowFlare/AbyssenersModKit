#include "character_species.h"

CharacterSpecies::CharacterSpecies() {}

void CharacterSpecies::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_sprites_dir", "value"), &CharacterSpecies::set_sprites_dir);
	ClassDB::bind_method(D_METHOD("get_sprites_dir"), &CharacterSpecies::get_sprites_dir);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "sprites_dir",
			PROPERTY_HINT_DIR
		),
		"set_sprites_dir", "get_sprites_dir"
	);
}

void CharacterSpecies::set_sprites_dir(String value) {
	sprites_dir = value;
}

String CharacterSpecies::get_sprites_dir() {
	return sprites_dir;
}