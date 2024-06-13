#include "core/config/engine.h"
#include "core/io/dir_access.h"
#include "core/string/string_builder.h"
#include "core/io/resource_loader.h"

#include "character_data.h"

#include "../nodes/common_components/gfx/sprite_component.h"

CharacterData::CharacterData() {
	required_components.push_back(SpriteComponent::get_class_static());

	Ref<CharacterLayerInfo> base = Ref<CharacterLayerInfo>(memnew(CharacterLayerInfo));
	base->set_layer_id("base");

	Ref<CharacterLayerInfo> left_eye = Ref<CharacterLayerInfo>(memnew(CharacterLayerInfo));
	left_eye->set_layer_id("left_eye");

	Ref<CharacterLayerInfo> right_eye = Ref<CharacterLayerInfo>(memnew(CharacterLayerInfo));
	right_eye->set_layer_id("right_eye");

	parts.push_back(base);
	parts.push_back(left_eye);
	parts.push_back(right_eye);
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

	ClassDB::bind_method(D_METHOD("set_parts", "value"), &CharacterData::set_parts);
	ClassDB::bind_method(D_METHOD("get_parts"), &CharacterData::get_parts);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "parts", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + ":" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "/" + CharacterLayerInfo::get_class_static()
		),
		"set_parts", "get_parts"
	);
	
	ClassDB::bind_method(D_METHOD("set_patterns", "value"), &CharacterData::set_patterns);
	ClassDB::bind_method(D_METHOD("get_patterns"), &CharacterData::get_patterns);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "patterns", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + ":" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "/" + CharacterLayerInfo::get_class_static()
		),
		"set_patterns", "get_patterns"
	);

	ClassDB::bind_method(D_METHOD("set_height", "value"), &CharacterData::set_height);
	ClassDB::bind_method(D_METHOD("get_height"), &CharacterData::get_height);
	ADD_PROPERTY(
		PropertyInfo(Variant::FLOAT, "height"),
		"set_height", "get_height"
	);

	ClassDB::bind_method(D_METHOD("set_width", "value"), &CharacterData::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &CharacterData::get_width);
	ADD_PROPERTY(
		PropertyInfo(Variant::FLOAT, "width"),
		"set_width", "get_width"
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

TypedArray<CharacterLayerInfo> CharacterData::get_parts() {
	return parts;
}

void CharacterData::set_parts(TypedArray<CharacterLayerInfo> value) {
	parts = value;
}

TypedArray<CharacterLayerInfo> CharacterData::get_patterns() {
	return patterns;
}

void CharacterData::set_patterns(TypedArray<CharacterLayerInfo> value) {
	patterns = value;
}

double CharacterData::get_height() {
	return height;
}

void CharacterData::set_height(double value) {
	height = value;
}

double CharacterData::get_width() {
	return width;
}

void CharacterData::set_width(double value) {
	width = value;
}