#include "core/config/engine.h"

#include "character_data.h"


void CharacterData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_data_path", "path"), &CharacterData::set_data_path);
	ClassDB::bind_method(D_METHOD("get_data_path"), &CharacterData::get_data_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "data_path", PropertyHint::PROPERTY_HINT_DIR),
		"set_data_path", "get_data_path"
	);
}

CharacterData::CharacterData() {}

void CharacterData::set_data_path(String path) {
	ERR_FAIL_COND_MSG(this->data_path != "" && !Engine::get_singleton()->is_editor_hint(), "The data_path for a character is already set");
	this->data_path = path;
}

String CharacterData::get_data_path() {
	return this->data_path;
}