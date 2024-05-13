#include "mod_loader.h"

#include "core/io/file_access_pack.h"
#include "scene/resources/packed_scene.h"

#include "../singletons/current_scene.h"
#include "load_fail.h"

ModLoader* ModLoader::singleton;

void ModLoader::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_content"), &ModLoader::load_content);
	ClassDB::bind_method(D_METHOD("is_mod_loaded", "mod_name"), &ModLoader::is_mod_loaded);

	ADD_SIGNAL(MethodInfo("mod_loaded", PropertyInfo(Variant::OBJECT, "mod", PROPERTY_HINT_RESOURCE_TYPE, "Mod", PROPERTY_USAGE_DEFAULT, ModInit::get_class_static())));
}

ModLoader::ModLoader() {
	singleton = this;
}

ModLoader* ModLoader::get_singleton() {
	return singleton;
}

void ModLoader::load_content() {
	ERR_FAIL_COND_MSG(already_loaded, "Mods have already been loaded, if you want to reload mods restart the game");
	already_loaded = true;

	for(int idx = 0; idx < load_order.get_list().size(); idx++) {
		String mod_file = load_order.get_list()[idx];
		Error result = PackedData::get_singleton()->add_pack("user://mods/" + mod_file + ".pck", true, 0);
		ERR_CONTINUE_MSG(result != OK, "Failed to load mod " + mod_file);
	}

	Ref<DirAccess> dir_ref = DirAccess::open("res://data/mod_inits");
	ERR_FAIL_COND_MSG(dir_ref.is_null(), "Could not open res://data/mod_inits");

	DirAccess *dir = dir_ref.ptr();
	dir->set_include_hidden(true);
	ResourceLoader loader;
	TypedArray<Node> inits;

	for(String file_name_raw : dir->get_files()) {
		String file_name = file_name_raw.trim_suffix(".remap");
		Ref<Resource> res_ref = loader.load(dir->get_current_dir() + '/' + file_name);
		ERR_CONTINUE_MSG(res_ref.is_null(), file_name + " failed to load");
		ERR_CONTINUE_MSG(!res_ref.ptr()->is_class(PackedScene::get_class_static()), file_name + " is not a PackedScene");
		
		PackedScene *scn = cast_to<PackedScene>(res_ref.ptr());
		Node *init = scn->instantiate();
		init->set_name(file_name.trim_suffix(".tscn").trim_suffix(".scn"));
		add_child(init);
	}

	for(int c_idx = 0; c_idx < get_child_count(); c_idx++) {
		ERR_CONTINUE_MSG(!get_child(c_idx)->is_class(ModInit::get_class_static()), "A child to the ModLoader was not a ModInit");
		ModInit *init = cast_to<ModInit>(get_child(c_idx));

		init->call("_initialize");
		init->set_loaded();
	}

	TypedArray<ModInit> failing;
	for(int c_idx = 0; c_idx < get_child_count(); c_idx++) {
		ERR_CONTINUE_MSG(!get_child(c_idx)->is_class(ModInit::get_class_static()), "A child to the ModLoader was not a ModInit");
		ModInit *init = cast_to<ModInit>(get_child(c_idx));

		if(init->call("has_load_error")) {
			failing.append(init);
		}
	}

	if(failing.size() > 0) {
		LoadFail failure;
		failure.add_many_load_errors(failing);
		print_error(failure.get_output());
		ERR_FAIL_MSG("Failed to load mods, check game output for details");
	}

	CurrentScene::get_singleton()->set_scene("system/title");
}

bool ModLoader::has_mod(String mod_id) {
	return has_node(mod_id);
}

bool ModLoader::is_mod_loaded(String mod_id) {
	return has_mod(mod_id) && get_mod_init(mod_id)->is_loaded();
}

ModInit *ModLoader::get_mod_init(String mod_id) {
	return cast_to<ModInit>(get_node(mod_id));
}