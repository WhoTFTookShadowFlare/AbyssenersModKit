#include "core/config/engine.h"
#include "core/io/dir_access.h"
#include "core/string/string_builder.h"
#include "core/io/resource_loader.h"

#include "character_data.h"

#include "../nodes/common_components/gfx/sprite_component.h"

CharacterData::CharacterData() {
	required_components.push_back(SpriteComponent::get_class_static());
}

void CharacterData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_rotates_to_velocity", "value"), &CharacterData::set_rotates_to_velocity);
	ClassDB::bind_method(D_METHOD("get_rotates_to_velocity"), &CharacterData::get_rotates_to_velocity);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "rotates_to_velocity"), "set_rotates_to_velocity", "get_rotates_to_velocity");

	ClassDB::bind_method(D_METHOD("set_required_components", "value"), &CharacterData::set_required_components);
	ClassDB::bind_method(D_METHOD("get_required_components"), &CharacterData::get_required_components);
	ADD_PROPERTY(PropertyInfo(
			Variant::ARRAY, "required_components", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::STRING) + ":"
		),
		"set_required_components", "get_required_components"
	);
	
	ClassDB::bind_method(D_METHOD("set_species", "value"), &CharacterData::set_species);
	ClassDB::bind_method(D_METHOD("get_species"), &CharacterData::get_species);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species"), "set_species", "get_species");

	ClassDB::bind_method(D_METHOD("set_primary_color", "value"), &CharacterData::set_primary_color);
	ClassDB::bind_method(D_METHOD("get_primary_color"), &CharacterData::get_primary_color);
	ADD_PROPERTY(
		PropertyInfo(Variant::COLOR, "primary_color"),
		"set_primary_color", "get_primary_color"
	);

	ClassDB::bind_method(D_METHOD("set_left_eye_color", "value"), &CharacterData::set_left_eye_color);
	ClassDB::bind_method(D_METHOD("get_left_eye_color"), &CharacterData::get_left_eye_color);
	ADD_PROPERTY(
		PropertyInfo(Variant::COLOR, "left_eye_color"),
		"set_left_eye_color", "get_left_eye_color"
	);

	ClassDB::bind_method(D_METHOD("set_right_eye_color", "value"), &CharacterData::set_right_eye_color);
	ClassDB::bind_method(D_METHOD("get_right_eye_color"), &CharacterData::get_right_eye_color);
	ADD_PROPERTY(
		PropertyInfo(Variant::COLOR, "right_eye_color"),
		"set_right_eye_color", "get_right_eye_color"
	);
	
	ClassDB::bind_method(D_METHOD("set_patterns", "value"), &CharacterData::set_patterns);
	ClassDB::bind_method(D_METHOD("get_patterns"), &CharacterData::get_patterns);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "patterns", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + ":" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "/" + CharacterPatternInfo::get_class_static()
		),
		"set_patterns", "get_patterns"
	);
}

void CharacterData::set_required_components(TypedArray<String> value) {
	required_components = value;
}

TypedArray<String> CharacterData::get_required_components() {
	return required_components;
}

bool CharacterData::get_rotates_to_velocity() {
	return rotates_to_velo;
}

void CharacterData::set_rotates_to_velocity(bool value) {
	rotates_to_velo = value;
}

Ref<CharacterSpecies> CharacterData::get_species() {
	return species;
}

void CharacterData::set_species(Ref<CharacterSpecies> value) {
	species = value;
}

Color CharacterData::get_primary_color() {
	return pri_color;
}

void CharacterData::set_primary_color(Color value) {
	pri_color = value;
}

Color CharacterData::get_left_eye_color() {
	return l_eye_color;
}

void CharacterData::set_left_eye_color(Color value) {
	l_eye_color = value;
}

Color CharacterData::get_right_eye_color() {
	return r_eye_color;
}

void CharacterData::set_right_eye_color(Color value) {
	r_eye_color = value;
}

TypedArray<CharacterPatternInfo> CharacterData::get_patterns() {
	return patterns;
}

void CharacterData::set_patterns(TypedArray<CharacterPatternInfo> value) {
	patterns = value;
}
