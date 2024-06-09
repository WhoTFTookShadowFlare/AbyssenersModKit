#include "character_pattern_info.h"

CharacterPatternInfo::CharacterPatternInfo() {}

void CharacterPatternInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_pattern_color", "color"), &CharacterPatternInfo::set_pattern_color);
	ClassDB::bind_method(D_METHOD("get_pattern_color"), &CharacterPatternInfo::get_pattern_color);
	ADD_PROPERTY(
		PropertyInfo(Variant::COLOR, "pattern_color"),
		"set_pattern_color", "get_pattern_color"
	);

	ClassDB::bind_method(D_METHOD("set_pattern_id", "id"), &CharacterPatternInfo::set_pattern_id);
	ClassDB::bind_method(D_METHOD("get_pattern_id"), &CharacterPatternInfo::get_pattern_id);
	ADD_PROPERTY(
		PropertyInfo(Variant::STRING, "pattern_id"),
		"set_pattern_id", "get_pattern_id"
	);
}

Color CharacterPatternInfo::get_pattern_color() {
	return pattern_color;
}

void CharacterPatternInfo::set_pattern_color(Color value) {
	pattern_color = value;
}

String CharacterPatternInfo::get_pattern_id() {
	return pattern_id;
}

void CharacterPatternInfo::set_pattern_id(String id) {
	pattern_id = id;
}