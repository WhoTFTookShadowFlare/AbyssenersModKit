#include "register_types.h"

#include "core/object/class_db.h"

#include "characters/character_data.h"
#include "characters/world_character.h"

#include "mod_management/mod_init.h"
#include "mod_management/load_order.h"
#include "mod_management/mod_loader.h"

static ModLoader* ModLoaderPtr = nullptr;

void initialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<CharacterData>();
		ClassDB::register_class<WorldCharacter>();

		ClassDB::register_class<ModInit>();
		ClassDB::register_class<LoadOrder>();
		ClassDB::register_class<ModLoader>();
		ModLoaderPtr = memnew(ModLoader);
		Engine::get_singleton()->add_singleton(Engine::Singleton("ModLoader", ModLoader::get_singleton()));
		return;
	}
}

void uninitialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		memdelete(ModLoaderPtr);
		return;
	}
}