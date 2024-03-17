#include "register_types.h"

#include "core/object/class_db.h"

#include "characters/character_data.h"
#include "characters/world_character.h"

void initialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<CharacterData>();
	ClassDB::register_class<WorldCharacter>();
}

void uninitialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}