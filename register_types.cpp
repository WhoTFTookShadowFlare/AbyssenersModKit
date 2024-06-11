#include "register_types.h"

#include "core/object/class_db.h"
#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

#include "characters/nodes/character_group_manager.h"
#include "characters/nodes/base_character_group.h"
#include "characters/nodes/world_character.h"

#include "characters/nodes/common_components/ai_component.h"
#include "characters/nodes/common_components/inventory_component.h"
#include "characters/nodes/common_components/luck_component.h"

#include "characters/nodes/common_components/gfx/sprite_component.h"

#include "characters/nodes/common_components/mobility/friction_component.h"
#include "characters/nodes/common_components/mobility/gravity_component.h"
#include "characters/nodes/common_components/mobility/pathing_component.h"

#include "characters/nodes/common_components/survival/armor_component.h"
#include "characters/nodes/common_components/survival/dodge_component.h"
#include "characters/nodes/common_components/survival/health_component.h"

#include "resources/base_item.h"

#include "menu/base_menu_layer.h"
#include "menu/main_menu.h"

#include "mod_management/mod_init.h"
#include "mod_management/load_order.h"
#include "mod_management/mod_loader.h"

#include "resources/save_file.h"
#include "resources/camera_modifier.h"

#include "singletons/save_manager.h"
#include "singletons/current_scene.h"
#include "singletons/game_camera.h"
#include "menu/menu_stack.h"

static ModLoader* ModLoaderPtr = nullptr;
static SaveManager *SaveManagerPtr = nullptr;
static CurrentScene *CurrentScenePtr = nullptr;
static CharacterGroupManager *CharacterGroupManagerPtr = nullptr;
static GameCamera *GameCameraPtr = nullptr;
static MenuStack *MenuStackPtr = nullptr;

void initialize_abysseners_mod_kit_module(ModuleInitializationLevel p_level) {
	if(p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<DamageSource>();
		ClassDB::register_class<StatModifier>();

		ClassDB::register_class<CharacterSpecies>();
		ClassDB::register_class<CharacterLayerInfo>();
		ClassDB::register_class<CharacterData>();
		ClassDB::register_class<WorldCharacter>();

		ClassDB::register_class<AIComponent>();
		ClassDB::register_class<AITask>();

		ClassDB::register_class<SpriteComponent>();

		ClassDB::register_class<BaseItem>();
		ClassDB::register_class<InventoryComponent>();

		ClassDB::register_class<GravityComponent>();
		ClassDB::register_class<PathingComponent>();
		ClassDB::register_class<FrictionComponent>();
		ClassDB::register_class<LuckComponent>();
		ClassDB::register_class<HealthComponent>();
		ClassDB::register_class<ArmorComponent>();
		ClassDB::register_class<DodgeComponent>();

		ClassDB::register_class<BaseCharacterGroup>();
		ClassDB::register_class<BaseMenuLayer>();
		ClassDB::register_class<MainMenu>();

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

		ClassDB::register_class<CharacterGroupManager>();
		CharacterGroupManagerPtr = memnew(CharacterGroupManager);
		Engine::get_singleton()->add_singleton(Engine::Singleton("CharacterGroupManager", CharacterGroupManager::get_singleton()));
		CharacterGroupManager::get_singleton()->call_deferred("_setup");

		ClassDB::register_class<CameraModifier>();
		ClassDB::register_class<GameCamera>();
		GameCameraPtr = memnew(GameCamera);
		Engine::get_singleton()->add_singleton(Engine::Singleton("GameCamera", GameCamera::get_singleton()));
		GameCamera::get_singleton()->call_deferred("_setup");

		ClassDB::register_class<MenuStack>();
		MenuStackPtr = memnew(MenuStack);
		Engine::get_singleton()->add_singleton(Engine::Singleton("MenuStack", MenuStack::get_singleton()));
		MenuStack::get_singleton()->call_deferred("_setup");
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