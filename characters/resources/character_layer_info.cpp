#include "character_layer_info.h"

CharacterLayerInfo::CharacterLayerInfo() {}

void CharacterLayerInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_layer_color", "color"), &CharacterLayerInfo::set_layer_color);
	ClassDB::bind_method(D_METHOD("get_layer_color"), &CharacterLayerInfo::get_layer_color);
	ADD_PROPERTY(
		PropertyInfo(Variant::COLOR, "layer_color"),
		"set_layer_color", "get_layer_color"
	);

	ClassDB::bind_method(D_METHOD("set_layer_id", "id"), &CharacterLayerInfo::set_layer_id);
	ClassDB::bind_method(D_METHOD("get_layer_id"), &CharacterLayerInfo::get_layer_id);
	ADD_PROPERTY(
		PropertyInfo(Variant::STRING, "layer_id"),
		"set_layer_id", "get_layer_id"
	);
}

Color CharacterLayerInfo::get_layer_color() {
	return layer_color;
}

void CharacterLayerInfo::set_layer_color(Color value) {
	layer_color = value;
}

String CharacterLayerInfo::get_layer_id() {
	return layer_id;
}

void CharacterLayerInfo::set_layer_id(String id) {
	layer_id = id;
}