#include "character_group_manager.h"

#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

CharacterGroupManager *CharacterGroupManager::singleton;

CharacterGroupManager::CharacterGroupManager() {
	singleton = this;
	set_name("CharacterGroupManager");
}

void CharacterGroupManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_setup"), &CharacterGroupManager::_setup);

	ClassDB::bind_method(D_METHOD("add_group", "group"), &CharacterGroupManager::add_group);
	ClassDB::bind_method(D_METHOD("has_group", "name"), &CharacterGroupManager::has_group);
	ClassDB::bind_method(D_METHOD("get_group", "name"), &CharacterGroupManager::get_group);
}

void CharacterGroupManager::add_group(BaseCharacterGroup *group) {
	add_child(group);
}

bool CharacterGroupManager::has_group(String name) {
	return get_node_or_null(name) != nullptr;
}

BaseCharacterGroup *CharacterGroupManager::get_group(String name) {
	Node *target = get_node(name);
	if(target == nullptr) {
		print_error("Missing group: " + name);
		return nullptr;
	} 
	if(!target->is_class(BaseCharacterGroup::get_class_static())) {
		print_error("Group " + name + " was not a BaseCharacterGroup");
		return nullptr;
	}
	return cast_to<BaseCharacterGroup>(target);
}

void CharacterGroupManager::_setup() {
	SceneTree::get_singleton()->get_root()->add_child(this);
}

CharacterGroupManager *CharacterGroupManager::get_singleton() {
	return singleton;
}