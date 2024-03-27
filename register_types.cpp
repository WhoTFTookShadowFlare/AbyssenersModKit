#include "register_types.h"

#include "core/object/class_db.h"
#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

#include "characters/character_data.h"
#include "characters/world_character.h"

#include "mod_management/mod_init.h"
#include "mod_management/load_order.h"
#include "mod_management/mod_loader.h"

#include "resources/save_file.h"
#include "singletons/save_manager.h"
#include "singletons/current_scene.h"

static ModLoader* ModLoaderPtr = nullptr;
static SaveManager *SaveManagerPtr = nullptr;
static CurrentScene *CurrentScenePtr = nullptr;

void initialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<CharacterData>();
		ClassDB::register_class<WorldCharacter>();

		ClassDB::register_class<ModInit>();
		ClassDB::register_class<LoadOrder>();
		ClassDB::register_class<ModLoader>();
		ModLoaderPtr = memnew(ModLoader);
		Engine::get_singleton()->add_singleton(Engine::Singleton("ModLoader", ModLoader::get_singleton()));

		ClassDB::register_class<SaveFile>();
		ClassDB::register_class<SaveManager>();
		SaveManagerPtr = memnew(SaveManager);
		Engine::get_singleton()->add_singleton(Engine::Singleton("SaveManager", SaveManager::get_singleton()));

		ClassDB::register_class<CurrentScene>();
		CurrentScenePtr = memnew(CurrentScene);
		Engine::get_singleton()->add_singleton(Engine::Singleton("CurrentScene", CurrentScene::get_singleton()));
		CurrentScene::get_singleton()->call_deferred("_setup");
		return;
	}
}

void uninitialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		memdelete(ModLoaderPtr);
		memdelete(SaveManagerPtr);
		return;
	}
}