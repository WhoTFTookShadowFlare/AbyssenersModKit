#include "current_scene.h"

#include "scene/main/window.h"
#include "scene/resources/packed_scene.h"
#include "core/io/dir_access.h"

#include "save_manager.h"

CurrentScene *CurrentScene::singleton;

void CurrentScene::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_scene", "id"), &CurrentScene::set_scene);
	ClassDB::bind_method(D_METHOD("get_scene"), &CurrentScene::get_scene);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "scene"), "set_scene", "get_scene");

	ADD_SIGNAL(MethodInfo("scene_changed", PropertyInfo(Variant::STRING, "scene_id")));

	ClassDB::bind_method(D_METHOD("_setup"), &CurrentScene::_setup);
	ClassDB::bind_method(D_METHOD("save_scene_id", "save_file"), &CurrentScene::save_scene_id);
	ClassDB::bind_method(D_METHOD("load_scene_id", "save_file"), &CurrentScene::load_scene_id);
}

CurrentScene *CurrentScene::get_singleton() {
	return singleton;
}

CurrentScene::CurrentScene() {
	singleton = this;
}

void CurrentScene::set_scene(String id) {
	ERR_FAIL_COND_MSG(!DirAccess::dir_exists_absolute("res://data/scenes/" + id), "Missing scene " + id);

	for(int c_idx = 0; c_idx < get_child_count(); c_idx++) {
		get_child(c_idx)->queue_free();
	}

	Ref<DirAccess> dir = DirAccess::open("res://data/scenes/" + id);
	ERR_FAIL_COND_MSG(dir.is_null(), "Could not set scene to " + id);
	dir->set_include_hidden(true);

	ResourceLoader loader;

	for(String file_name_raw : dir->get_files()) {
		String file_name = file_name_raw.trim_suffix(".remap");
		Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file_name);
		ERR_CONTINUE_MSG(res.is_null(), "Failed to load " + file_name);
		ERR_CONTINUE_MSG(!res.ptr()->is_class(PackedScene::get_class_static()), file_name + " was not a PackedScene");

		PackedScene *scn = cast_to<PackedScene>(res.ptr());

		Node *node = scn->instantiate();
		node->set_name(file_name.trim_suffix(".tscn").trim_suffix(".scn"));
		add_child(node);
	}

	scene_id = id;
	emit_signal("scene_changed", id);
}

String CurrentScene::get_scene() {
	return scene_id;
}

void CurrentScene::_setup() {
	Window *win = SceneTree::get_singleton()->get_root();
	win->add_child(this);

	SaveManager *sv_mgr = SaveManager::get_singleton();
	sv_mgr->connect("save_game_file", Callable(this, "save_scene_id"));
	sv_mgr->connect("load_game_file", Callable(this, "load_scene_id"));
}

void CurrentScene::save_scene_id(SaveFile *file) {
	file->set_data("system/scene", get_scene());
}

void CurrentScene::load_scene_id(SaveFile *file) {
	if(!file->has_data("system/scene")) {
		return;
	}

	set_scene(file->get_data("system/scene").stringify());
}