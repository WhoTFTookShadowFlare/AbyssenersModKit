#include "character_data.h"

#include "core/config/engine.h"
#include "core/io/dir_access.h"
#include "core/string/string_builder.h"
#include "core/io/resource_loader.h"
#include "scene/2d/animated_sprite_2d.h"

#include "../nodes/common_components/gfx/sprite_component.h"

CharacterData::CharacterData() {}

void CharacterData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_rotates_to_velocity", "value"), &CharacterData::set_rotates_to_velocity);
	ClassDB::bind_method(D_METHOD("get_rotates_to_velocity"), &CharacterData::get_rotates_to_velocity);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "rotates_to_velocity"), "set_rotates_to_velocity", "get_rotates_to_velocity");

	ClassDB::bind_method(D_METHOD("set_required_components", "value"), &CharacterData::set_required_components);
	ClassDB::bind_method(D_METHOD("get_required_components"), &CharacterData::get_required_components);
	ADD_PROPERTY(PropertyInfo(
			Variant::ARRAY, "required_components", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::DICTIONARY) + ":" + String::num(PROPERTY_HINT_TYPE_STRING)
		),
		"set_required_components", "get_required_components"
	);
	
	ClassDB::bind_method(D_METHOD("set_species", "value"), &CharacterData::set_species);
	ClassDB::bind_method(D_METHOD("get_species"), &CharacterData::get_species);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species"), "set_species", "get_species");

	ClassDB::bind_method(D_METHOD("set_parts", "value"), &CharacterData::set_parts);
	ClassDB::bind_method(D_METHOD("get_parts"), &CharacterData::get_parts);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "parts", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + ":" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "/" + CharacterLayerInfo::get_class_static()
		),
		"set_parts", "get_parts"
	);
	
	ClassDB::bind_method(D_METHOD("set_patterns", "value"), &CharacterData::set_patterns);
	ClassDB::bind_method(D_METHOD("get_patterns"), &CharacterData::get_patterns);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "patterns", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + ":" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "/" + CharacterLayerInfo::get_class_static()
		),
		"set_patterns", "get_patterns"
	);

	ClassDB::bind_method(D_METHOD("set_height", "value"), &CharacterData::set_height);
	ClassDB::bind_method(D_METHOD("get_height"), &CharacterData::get_height);
	ADD_PROPERTY(
		PropertyInfo(Variant::FLOAT, "height"),
		"set_height", "get_height"
	);

	ClassDB::bind_method(D_METHOD("set_width", "value"), &CharacterData::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &CharacterData::get_width);
	ADD_PROPERTY(
		PropertyInfo(Variant::FLOAT, "width"),
		"set_width", "get_width"
	);

	ClassDB::bind_method(D_METHOD("get_talk_sprite"), &CharacterData::get_talk_sprite);
	ClassDB::bind_method(D_METHOD("get_char_icon"), &CharacterData::get_char_icon);
}

void CharacterData::set_required_components(TypedArray<Dictionary> value) {
	required_components = value;
}

TypedArray<Dictionary> CharacterData::get_required_components() {
	return required_components;
}

bool CharacterData::get_rotates_to_velocity() {
	return rotates_to_velo;
}

void CharacterData::set_rotates_to_velocity(bool value) {
	rotates_to_velo = value;
}

Ref<CharacterSpecies> CharacterData::get_species() {
	return species;
}

void CharacterData::set_species(Ref<CharacterSpecies> value) {
	species = value;
}

TypedArray<CharacterLayerInfo> CharacterData::get_parts() {
	return parts;
}

void CharacterData::set_parts(TypedArray<CharacterLayerInfo> value) {
	parts = value;
}

TypedArray<CharacterLayerInfo> CharacterData::get_patterns() {
	return patterns;
}

void CharacterData::set_patterns(TypedArray<CharacterLayerInfo> value) {
	patterns = value;
}

double CharacterData::get_height() {
	return height;
}

void CharacterData::set_height(double value) {
	height = value;
}

double CharacterData::get_width() {
	return width;
}

void CharacterData::set_width(double value) {
	width = value;
}

Node2D *CharacterData::add_char_sprites_to(TypedArray<CharacterLayerInfo> layers, String anim_name) {
	ERR_FAIL_COND_V_MSG(species.is_null(), nullptr, "No species provided to generate sprite for");

	Node2D *sprites = memnew(Node2D);
	for(Variant var : layers) {
		if(var.get_type() != Variant::OBJECT) continue;
		Object *obj = var.operator Object *();
		if(!obj->is_class(CharacterLayerInfo::get_class_static())) continue;
		CharacterLayerInfo *layer_info = cast_to<CharacterLayerInfo>(obj);

		Ref<SpriteFrames> species_anim_data = species->get_animation_data();

		AnimatedSprite2D *layer_spr = memnew(AnimatedSprite2D);
		layer_spr->set_sprite_frames(species_anim_data);
		layer_spr->set_modulate(layer_info->get_layer_color());
		layer_spr->set_centered(false);

		if(species_anim_data->has_animation(layer_info->get_layer_id() + ':' + anim_name))
			layer_spr->set_animation(layer_info->get_layer_id() + ':' + anim_name);
		else
			layer_spr->set_visible(false);
		
		sprites->add_child(layer_spr);
		layer_spr->set_name(layer_info->get_layer_id());
	}
	return sprites;
}

SubViewport *CharacterData::get_talk_sprite(String expression) {
	ERR_FAIL_COND_V_MSG(species.is_null(), nullptr, "A CharacterData does not have a CharacterSpecies");
	
	Node2D *base_spr = add_char_sprites_to(parts, "talk." + expression);
	Node2D *layer_spr = add_char_sprites_to(patterns, "talk." + expression);

	ERR_FAIL_COND_V_MSG(base_spr == nullptr, nullptr, "Failed to generate talk sprite");

	SubViewport *sprite = memnew(SubViewport);
	sprite->set_size(Vector2i(16, 16));
	sprite->set_transparent_background(true);
	sprite->set_disable_3d(true);
	sprite->set_default_canvas_item_texture_filter(Viewport::DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST);
	
	sprite->add_child(base_spr);
	sprite->add_child(layer_spr);
	return sprite;
}

SubViewport *CharacterData::get_char_icon() {
	return get_talk_sprite("happy");
}
