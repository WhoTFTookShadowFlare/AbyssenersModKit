#include "game_camera.h"

#include "scene/main/window.h"

#include "save_manager.h"

GameCamera *GameCamera::singleton;

void GameCamera::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_setup"), &GameCamera::_setup);

	ClassDB::bind_method(D_METHOD("_save", "file"), &GameCamera::_save);
	ClassDB::bind_method(D_METHOD("_load", "file"), &GameCamera::_load);
}

GameCamera *GameCamera::get_singleton() {
	return singleton;
}

GameCamera::GameCamera() {
	singleton = this;
}

void GameCamera::_setup() {
	Window *win = SceneTree::get_singleton()->get_root();
	win->add_child(this);

	SaveManager *sv = SaveManager::get_singleton();
	sv->connect("save_game_file", Callable(this, "_save"));
	sv->connect("load_game_file", Callable(this, "_load"));
}

void GameCamera::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
		case NOTIFICATION_READY: {
			set_process_internal(true);
			set_current(true);
		}; break;
		case NOTIFICATION_INTERNAL_PROCESS: {
			for(int idx = 0; idx < modifiers.size(); idx++) {
				Ref<CameraModifier> mod = modifiers[idx];
				mod->call("update_camera", this);
			}
		}; break;
	}
}

void GameCamera::_save(Ref<SaveFile> file) {
	file->set_data("sys/cam/mods", modifiers);
}

void GameCamera::_load(Ref<SaveFile> file) {
	if(!file->has_data("sys/cam/mods")) return;
	ERR_FAIL_COND_MSG(!file->get_data("sys/cam/mods").is_array(), "Wrong type for 'sys/cam/mods', expected an array");
	modifiers = (TypedArray<CameraModifier>) file->get_data("sys/cam/mods");
}