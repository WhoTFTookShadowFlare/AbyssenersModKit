#include "base_character_group.h"

#include "core/io/file_access.h"
#include "core/io/dir_access.h"
#include "scene/resources/packed_scene.h"

#include "../../singletons/save_manager.h"

BaseCharacterGroup::BaseCharacterGroup() {
	SaveManager *sv_mgr = SaveManager::get_singleton();

	sv_mgr->connect("save_game_file", Callable(this, "save_characters"));
	sv_mgr->connect("load_game_file", Callable(this, "load_characters"));
}

void BaseCharacterGroup::_bind_methods() {
	PackedStringArray can_spawn_args;
	can_spawn_args.append("character_data");
	ClassDB::add_virtual_method(BaseCharacterGroup::get_class_static(), 
		MethodInfo(Variant::BOOL, "can_spawn",
			PropertyInfo(
				Variant::OBJECT, "character_data",
				PROPERTY_HINT_RESOURCE_TYPE, CharacterData::get_class_static()
			)
		),
		true, can_spawn_args
	);

	ClassDB::bind_method(D_METHOD("try_spawn_character", "character_data"), &BaseCharacterGroup::try_spawn_character);

	ADD_SIGNAL(MethodInfo("character_spawned", PropertyInfo(Variant::OBJECT, "world_character")));

	ClassDB::bind_method(D_METHOD("save_characters", "save_file"), &BaseCharacterGroup::save_characters);
	ClassDB::bind_method(D_METHOD("load_characters", "load_file"), &BaseCharacterGroup::load_characters);
}

WorldCharacter *BaseCharacterGroup::try_spawn_character(Ref<CharacterData> data) {
	if(!call("can_spawn", data)) {
		return nullptr;
	}

	WorldCharacter *character = memnew(WorldCharacter);
	character->set_character_data(data);

	for(Variant component_var : character->get_character_data()->get_required_components()) {
		if(component_var.get_type() != Variant::STRING) continue;
		String component_id = component_var.operator String();
		if(!ClassDB::can_instantiate(component_id)) {
			print_line("Cannot instance " + component_id);
			continue;
		}

		Object *obj = ClassDB::instantiate(component_id);
		if(!obj->is_class(Node::get_class_static())) {
			memfree(obj);
			continue;
		}

		Node *comp = cast_to<Node>(obj);
		character->add_child(comp);
		comp->set_owner(character);
	}

	add_child(character);
	emit_signal("character_spawned", character);
	return character;
}

void BaseCharacterGroup::save_characters(SaveFile *file) {
	TypedArray<PackedScene> character_scenes;
	for(int c_idx = 0; c_idx < get_child_count(); c_idx++) {
		Node *child = get_child(c_idx);
		ERR_CONTINUE_MSG(!child->is_class(WorldCharacter::get_class_static()), "A child to a character group was not a WorldCharacter");

		Ref<PackedScene> scn = memnew(PackedScene);
		scn->pack(child);
		character_scenes.append(scn);
	}
	file->set_data("system/char_groups/" + get_name(), character_scenes);
}

void BaseCharacterGroup::load_characters(SaveFile *file) {
	if(!file->has_data("system/char_groups/" + get_name())) {
		return;
	}
	Variant characters_var = file->get_data("system/char_groups/" + get_name());
	ERR_FAIL_COND(!characters_var.is_array());
	
	for(int c_idx = 0; c_idx < get_child_count(); c_idx++) {
		get_child(c_idx)->queue_free();
	}

	TypedArray<PackedScene> characters = characters_var;
	for(int scn_idx = 0; scn_idx < characters.size(); scn_idx++) {
		PackedScene *scn = cast_to<PackedScene>(characters[scn_idx]);
		WorldCharacter *character_node = cast_to<WorldCharacter>(scn->instantiate());
		add_child(character_node);
		emit_signal("character_spawned", character_node);
	}
}