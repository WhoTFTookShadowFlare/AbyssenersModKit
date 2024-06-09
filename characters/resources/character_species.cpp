#include "character_species.h"

CharacterSpecies::CharacterSpecies() {}

void CharacterSpecies::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_animations_dir", "value"), &CharacterSpecies::set_animations_dir);
	ClassDB::bind_method(D_METHOD("get_animations_dir"), &CharacterSpecies::get_animations_dir);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "animations_dir",
			PROPERTY_HINT_DIR
		),
		"set_animations_dir", "get_animations_dir"
	);

	ClassDB::bind_method(D_METHOD("set_default_stat_modifiers", "value"), &CharacterSpecies::set_default_stat_modifiers);
	ClassDB::bind_method(D_METHOD("get_default_stat_modifiers"), &CharacterSpecies::get_default_stat_modifiers);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "default_stat_modifiers",
			PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":" + StatModifier::get_class_static()
		),
		"set_default_stat_modifiers", "get_default_stat_modifiers"
	);
}

void CharacterSpecies::set_animations_dir(String value) {
	anims_dir = value;
}

String CharacterSpecies::get_animations_dir() {
	return anims_dir;
}

void CharacterSpecies::set_default_stat_modifiers(TypedArray<StatModifier> value) {
	default_stat_modifiers = value;
}

TypedArray<StatModifier> CharacterSpecies::get_default_stat_modifiers() {
	return default_stat_modifiers;
}
