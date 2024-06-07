#include "core/config/engine.h"
#include "core/io/dir_access.h"
#include "core/string/string_builder.h"
#include "core/io/resource_loader.h"

#include "character_data.h"


void CharacterData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_data_path", "path"), &CharacterData::set_data_path);
	ClassDB::bind_method(D_METHOD("get_data_path"), &CharacterData::get_data_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "data_path", PropertyHint::PROPERTY_HINT_DIR),
		"set_data_path", "get_data_path"
	);

	ClassDB::bind_method(D_METHOD("get_sub_resources", "sub_resource_id"), &CharacterData::get_sub_resources);

	ClassDB::bind_method(D_METHOD("set_rotates_to_velocity", "value"), &CharacterData::set_rotates_to_velocity);
	ClassDB::bind_method(D_METHOD("get_rotates_to_velocity"), &CharacterData::get_rotates_to_velocity);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "rotates_to_velocity"), "set_rotates_to_velocity", "get_rotates_to_velocity");
}

CharacterData::CharacterData() {}

void CharacterData::set_data_path(String path) {
	ERR_FAIL_COND_MSG(this->data_path != "" && !Engine::get_singleton()->is_editor_hint(), "The data_path for a character is already set");
	this->data_path = path;
}

String CharacterData::get_data_path() {
	return this->data_path + '/';
}

Ref<Resource> CharacterData::get_resource(String resource_id) {
	if(!DirAccess::exists("res://data/characters/" + get_data_path() + resource_id)) {
		ERR_PRINT("Missing " + resource_id + " for " + data_path);
		return Ref<Resource>();
	}

	ResourceLoader loader;
	return loader.load("res://data/characters/" + get_data_path() + resource_id);
}

TypedArray<Resource> CharacterData::get_sub_resources(String sub_resource_id) {
	Ref<DirAccess> dir_ref = DirAccess::open(get_data_path() + sub_resource_id);
	if(dir_ref.is_null()) {
		StringBuilder builder;
		builder.append("Could not open directory ").append(get_data_path() + sub_resource_id);
		ERR_PRINT(builder.as_string());
		return TypedArray<Resource>();
	}

	DirAccess *dir = dir_ref.ptr();
	dir->set_include_hidden(true);
	ResourceLoader loader;
	TypedArray<Resource> resources;

	PackedStringArray files = dir->get_files();
	for(String file_name : files) {
		Ref<Resource> res_ref = loader.load(get_data_path() + sub_resource_id + '/' + file_name);
		if(res_ref.is_null()) {
			WARN_PRINT("Failed to load " + file_name);
			continue;
		}

		resources.append(res_ref.ptr());
	}

	return resources;
}

bool CharacterData::get_rotates_to_velocity() {
	return rotates_to_velo;
}

void CharacterData::set_rotates_to_velocity(bool value) {
	rotates_to_velo = value;
}