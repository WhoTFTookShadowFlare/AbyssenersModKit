#include "character_species.h"

#include "scene/resources/sprite_frames.h"
#include "core/io/dir_access.h"

CharacterSpecies::CharacterSpecies() {}

void CharacterSpecies::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_animations_dir", "value"), &CharacterSpecies::set_animations_dir);
	ClassDB::bind_method(D_METHOD("get_animations_dir"), &CharacterSpecies::get_animations_dir);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "animations_dir",
			PROPERTY_HINT_DIR
		),
		"set_animations_dir", "get_animations_dir"
	);

	ClassDB::bind_method(D_METHOD("set_default_stat_modifiers", "value"), &CharacterSpecies::set_default_stat_modifiers);
	ClassDB::bind_method(D_METHOD("get_default_stat_modifiers"), &CharacterSpecies::get_default_stat_modifiers);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "default_stat_modifiers",
			PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":" + StatModifier::get_class_static()
		),
		"set_default_stat_modifiers", "get_default_stat_modifiers"
	);

	ClassDB::bind_method(D_METHOD("get_animation_data"), &CharacterSpecies::get_animation_data);
}

void CharacterSpecies::set_animations_dir(String value) {
	anims_dir = value;
}

String CharacterSpecies::get_animations_dir() {
	return anims_dir;
}

void CharacterSpecies::set_default_stat_modifiers(TypedArray<StatModifier> value) {
	default_stat_modifiers = value;
}

TypedArray<StatModifier> CharacterSpecies::get_default_stat_modifiers() {
	return default_stat_modifiers;
}

Ref<SpriteFrames> CharacterSpecies::get_animation_data() {
	if(animation_data.is_valid()) return animation_data;

	animation_data = Ref<SpriteFrames>(memnew(SpriteFrames));

	if(!DirAccess::dir_exists_absolute(anims_dir)) {
		_err_print_error(FUNCTION_STR, __FILE__, __LINE__, "Method/function failed.", "Missing animation directory '" + anims_dir + "'");
		return animation_data;
	}

	Ref<DirAccess> dir = DirAccess::open(anims_dir);
	if(dir.is_null()) {
		_err_print_error(FUNCTION_STR, __FILE__, __LINE__, "Method/function failed.", "Failed to open '" + anims_dir + "'");
		return animation_data;
	}

	ResourceLoader loader;
	for(String file : dir->get_files()) {
		Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file);
		ERR_CONTINUE_MSG(res.is_null(), "Failed to load: " + dir->get_current_dir() + '/' + file);
		ERR_CONTINUE_MSG(!res->is_class(SpriteFrames::get_class_static()), file + " was not a SpriteFrames");
		SpriteFrames *frames = cast_to<SpriteFrames>(res.ptr());
		
		List<StringName> animations;
		frames->get_animation_list(&animations);
		for(StringName animation_name : animations) {
			if(animation_data->has_animation(animation_name)) {
				animation_data->clear(animation_name);
				animation_data->set_animation_loop(animation_name, frames->get_animation_loop(animation_name));
				animation_data->set_animation_speed(animation_name, frames->get_animation_speed(animation_name));
			}
			else animation_data->add_animation(animation_name);

			for(int f_idx = 0; f_idx < frames->get_frame_count(animation_name); f_idx++) {
				animation_data->add_frame(
					animation_name,
					frames->get_frame_texture(animation_name, f_idx),
					frames->get_frame_duration(animation_name, f_idx)
				);
			}
		}
	}

	return animation_data;
}
