#include "save_manager.h"

#include "core/io/file_access.h"
#include "core/io/dir_access.h"
#include "core/io/resource_loader.h"
#include "core/io/resource_saver.h"
#include "core/core_bind.h"
#include "core/config/engine.h"

SaveManager *SaveManager::singleton;

void SaveManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_save_files"), &SaveManager::get_save_files);
	ClassDB::bind_method(D_METHOD("write_save_file"), &SaveManager::write_save_files);

	ClassDB::bind_method(D_METHOD("get_global_file_path"), &SaveManager::get_global_file_path);

	ADD_SIGNAL(MethodInfo("setup_game_file"));
	ADD_SIGNAL(MethodInfo("save_game_file", PropertyInfo(Variant::OBJECT, "file")));
	ADD_SIGNAL(MethodInfo("load_game_file", PropertyInfo(Variant::OBJECT, "file")));

	ClassDB::bind_method(D_METHOD("get_global_file"), &SaveManager::get_global_file);
	ClassDB::bind_method(D_METHOD("get_game_file"), &SaveManager::get_game_file);

	ClassDB::bind_method(D_METHOD("get_game_file_name"), &SaveManager::get_game_file_name);
	ClassDB::bind_method(D_METHOD("set_game_file_name", "file_name"), &SaveManager::set_game_file_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "game_file_name"), "set_game_file_name", "get_game_file_name");
}

SaveManager::SaveManager() {
	singleton = this;
	if(Engine::get_singleton()->is_editor_hint()) return;

	if(!FileAccess::exists(get_global_file_path())
	) {
		global_file = Ref<SaveFile>(memnew(SaveFile));
		return;
	}
	
	ResourceLoader loader;
	global_file = Ref<SaveFile>(cast_to<SaveFile>(loader.load(get_global_file_path()).ptr()));
}

SaveManager::~SaveManager() {
	write_save_files();
}

SaveManager *SaveManager::get_singleton() {
	return singleton;
}

String SaveManager::get_global_file_path() const {
#ifdef DEBUG_ENABLED
	return "user://global.tres";
#else
	return "user://global.res";
#endif
}

PackedStringArray SaveManager::get_save_files() {
	Ref<DirAccess> dir = DirAccess::open("user://saves");
	if(dir.is_null()) {
		PackedStringArray arr;
		return arr;
	}
	dir->set_include_hidden(true);
	PackedStringArray filtered;
	for(String file_name : dir->get_files()) {
		if(file_name.ends_with(
#ifdef DEBUG_ENABLED
			".tres"
#else
			".res"
#endif
		)) filtered.append(file_name.trim_suffix(".tres").trim_suffix(".res"));
	}
	return filtered;
}

void SaveManager::write_save_files() {
	if(Engine::get_singleton()->is_editor_hint()) return;
	
	if(!DirAccess::dir_exists_absolute("user://saves"))
		DirAccess::make_dir_recursive_absolute("user://saves");

	ResourceSaver saver;

	if(global_file.is_valid())
		saver.save(global_file.ptr(), get_global_file_path());

	if(game_file.is_valid())
		saver.save(game_file.ptr(), "user://saves/" + game_file_name + 
#ifdef DEBUG_ENABLED
	".tres"
#else
	".res"
#endif
	);
}

Ref<SaveFile> SaveManager::get_game_file() {
	return game_file;
}

Ref<SaveFile> SaveManager::get_global_file() {
	return global_file;
}

void SaveManager::set_game_file_name(String file_name) {
	if(file_name == "") {
		write_save_files();
		game_file = Ref<SaveFile>();
		game_file_name = "";
		return;
	}

	String target_file = "user://saves/" + file_name + 
#ifdef DEBUG_ENABLED
		".tres";
#else
		".res";
#endif
	if(!FileAccess::exists(target_file)) { ERR_FAIL_MSG("Could not find file " + target_file); }
	write_save_files();

	ResourceLoader loader;
	game_file = loader.load(target_file);
	game_file_name = target_file.trim_prefix("user://saves/");
}

String SaveManager::get_game_file_name() {
	return game_file_name;
}