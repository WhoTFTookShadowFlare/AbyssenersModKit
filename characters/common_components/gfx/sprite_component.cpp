#include "sprite_component.h"

#include "core/io/dir_access.h"

#include "scene/main/window.h"
#include "scene/main/node.h"
#include "scene/3d/camera_3d.h"

#include "core/math/math_funcs.h"

void SpriteComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_current_frame", "value"), &SpriteComponent::set_current_frame);
	ClassDB::bind_method(D_METHOD("get_current_frame"), &SpriteComponent::get_current_frame);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current_frame"), "set_current_frame", "get_current_frame");

	ClassDB::bind_method(D_METHOD("set_frame_time_remaining", "value"), &SpriteComponent::set_frame_time_remaining);
	ClassDB::bind_method(D_METHOD("get_frame_time_remaining"), &SpriteComponent::get_frame_time_remaining);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frame_time_remaining"), "set_frame_time_remaining", "get_frame_time_remaining");

	ClassDB::bind_method(D_METHOD("set_animations_location", "value"), &SpriteComponent::set_animations_location);
	ClassDB::bind_method(D_METHOD("get_animations_location"), &SpriteComponent::get_animations_location);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "animations_location"), "set_animations_location", "get_animations_location");

	ClassDB::bind_method(D_METHOD("set_current_animation", "value"), &SpriteComponent::set_current_animation);
	ClassDB::bind_method(D_METHOD("get_current_animation"), &SpriteComponent::get_current_animation);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "current_animation"), "set_current_animation", "get_current_animation");

	ClassDB::bind_method(D_METHOD("set_direction_count", "value"), &SpriteComponent::set_direction_count);
	ClassDB::bind_method(D_METHOD("get_direction_count"), &SpriteComponent::get_direction_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "direction_count"), "set_direction_count", "get_direction_count");

	ClassDB::bind_method(D_METHOD("set_cw_rotation", "value"), &SpriteComponent::set_cw_rotation);
	ClassDB::bind_method(D_METHOD("get_cw_rotation"), &SpriteComponent::get_cw_rotation);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cw_rotation"), "set_cw_rotation", "get_cw_rotation");

	ClassDB::bind_method(D_METHOD("set_rotation_frame_offset", "value"), &SpriteComponent::set_rotation_frame_offset);
	ClassDB::bind_method(D_METHOD("get_rotation_frame_offset"), &SpriteComponent::get_rotation_frame_offset);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rotation_frame_offset"), "set_rotation_frame_offset", "get_rotation_frame_offset");
	

	ADD_SIGNAL(MethodInfo("animation_changed"));
}

SpriteComponent::SpriteComponent() {}

void SpriteComponent::_notification(int p_what) {
	switch(p_what) {
	case NOTIFICATION_READY: {
		set_process_internal(true);

		set_billboard_mode(StandardMaterial3D::BillboardMode::BILLBOARD_FIXED_Y);
		set_texture_filter(StandardMaterial3D::TextureFilter::TEXTURE_FILTER_NEAREST_WITH_MIPMAPS);
		set_draw_flag(SpriteBase3D::FLAG_SHADED, true);
		set_alpha_cut_mode(SpriteBase3D::ALPHA_CUT_OPAQUE_PREPASS);
	}; break;
	case NOTIFICATION_INTERNAL_PROCESS: {
		if(!Engine::get_singleton()->is_editor_hint())
			set_frame_time_remaining(frame_time_rem - get_process_delta_time());

		Viewport *view = get_viewport();
		if(!view) return;

		Camera3D *cam = view->get_camera_3d();
		if(!cam) return;

		double angle_diff = Math::wrapf(Math::rad_to_deg(get_global_rotation().y - cam->get_global_rotation().y) + ANGLE_START_OFF, 0.0, 360.0);
		int spr_idx;
		if(cw_rotation) spr_idx = (int) Math::floor(angle_diff / ANGLE_BETWEEN);
		else spr_idx = (int) Math::ceil(-angle_diff / ANGLE_BETWEEN);
		Sprite3D::set_frame(Math::wrapi(spr_idx + rotation_frame_offset, 0, direction_count));

	}; break;
	default:
		break;
	}
}

void SpriteComponent::update_texture() {
	set_texture(animation_data->get_frame_texture(get_current_animation(), get_current_frame()));
}

void SpriteComponent::set_cw_rotation(bool value) {
	cw_rotation = value;
}

bool SpriteComponent::get_cw_rotation() {
	return cw_rotation;
}

void SpriteComponent::set_rotation_frame_offset(int value) {
	rotation_frame_offset = value;
}

int SpriteComponent::get_rotation_frame_offset() {
	return rotation_frame_offset;
}

void SpriteComponent::set_current_animation(String value) {
	if(Engine::get_singleton()->is_editor_hint()) {
		current_animation = value;
		if(!animation_data->has_animation(value))
			return;
	}

	ERR_FAIL_COND_MSG(!animation_data->has_animation(value), "Missing animation: " + value);
	ERR_FAIL_COND_MSG(animation_data->get_frame_count(value) < 1, "Animation '" + value + "' has no frames");
	current_animation = value;
	current_frame = 0;
	frame_time_rem = animation_data->get_frame_duration(value, 0);
	update_texture();
	emit_signal("animation_changed");

	if(value == ANIMATION_ERROR) set_hframes(1);
	else set_hframes(direction_count);
}

String SpriteComponent::get_current_animation() {
	return current_animation;
}

void SpriteComponent::set_current_frame(int value) {
	int anim_frame_count = animation_data->get_frame_count(current_animation);
	current_frame = Math::wrapi(value, 0, anim_frame_count);
	update_texture();
	emit_signal("frame_changed");
}

int SpriteComponent::get_current_frame() {
	return current_frame;
}

void SpriteComponent::set_frame_time_remaining(float value) {
	frame_time_rem = value;
	if(frame_time_rem > 0.0) return;

	while(frame_time_rem < 0.0) {
		set_current_frame(current_frame + 1);
		frame_time_rem += animation_data->get_frame_duration(current_animation, current_frame);
	}
}

float SpriteComponent::get_frame_time_remaining() {
	return frame_time_rem;
}

void SpriteComponent::set_animations_location(String value) {
	if(Engine::get_singleton()->is_editor_hint()) {
		animations_location = value;
		if(!DirAccess::dir_exists_absolute("res://assets/animations/" + value)) return;
	}
	
	ERR_FAIL_COND(!DirAccess::dir_exists_absolute("res://assets/animations/" + value));

	animations_location = value;

	Ref<DirAccess> dir = DirAccess::open("res://assets/animations/" + value);
	ResourceLoader loader;

	animation_data = Ref<SpriteFrames>(memnew(SpriteFrames));
	animation_data->add_animation(ANIMATION_ERROR);
	animation_data->add_frame(ANIMATION_ERROR, loader.load("res://assets/sprites/error.png"));
	current_animation = ANIMATION_ERROR;
	current_frame = 0;
	frame_time_rem = 0.0;

	for(String file : dir->get_files()) {
		Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file);
		ERR_CONTINUE_MSG(!res->is_class(SpriteFrames::get_class_static()), "A resource in '" + dir->get_current_dir() + "' was not a SpriteFrames");

		print_verbose("Merging animations from file '" + file + "'");

		SpriteFrames *frames = cast_to<SpriteFrames>(res.ptr());
		for(String anim : frames->get_animation_names()) {
			if(!animation_data->has_animation(anim)) {
				animation_data->add_animation(anim);
				print_verbose("Adding animation: " + anim);
			}
			else {
				animation_data->clear(anim);
				print_verbose("Replacing animation: " + anim);
			}

			for(int idx = 0; idx < frames->get_frame_count(anim); idx++) {
				animation_data->add_frame(anim, frames->get_frame_texture(anim, idx), frames->get_frame_duration(anim, idx));
			}
		}
	}

	update_texture();
}

String SpriteComponent::get_animations_location() {
	return animations_location;
}

void SpriteComponent::set_direction_count(int value) {
	direction_count = value;
	set_hframes(value);

	ANGLE_BETWEEN = 360.0 / (double) direction_count;
	ANGLE_START_OFF = ANGLE_BETWEEN / 2.0;
}

int SpriteComponent::get_direction_count() {
	return direction_count;
}
