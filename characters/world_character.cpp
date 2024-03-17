#include "core/config/engine.h"

#include "world_character.h"

void WorldCharacter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_character_data", "data"), &WorldCharacter::set_character_data);
	ClassDB::bind_method(D_METHOD("get_character_data"), &WorldCharacter::get_character_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "data", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE),
		"set_character_data", "get_character_data"
	);
}

WorldCharacter::WorldCharacter() {}

void WorldCharacter::set_character_data(Ref<CharacterData> data_ref) {
	ERR_FAIL_COND_MSG(this->data.is_valid() && !Engine::get_singleton()->is_editor_hint(), "A character already has data set");
	this->data = data_ref;
}

Ref<CharacterData> WorldCharacter::get_character_data() {
	return this->data;
}