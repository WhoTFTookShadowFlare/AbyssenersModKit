#include "sprite_component.h"

#include "scene/2d/animated_sprite_2d.h"

#include "../../world_character.h"

SpriteComponent::SpriteComponent() {
	render = memnew(SubViewport);
	render->set_disable_3d(true);
	render->set_default_canvas_item_texture_filter(Viewport::DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST);
	render->set_transparent_background(true);
	add_child(render);

	render_texture = Ref<ViewportTexture>(memnew(ViewportTexture));

	char_layers = memnew(Node2D);
	render->add_child(char_layers);

	char_equip = memnew(Node2D);
	render->add_child(char_equip);

	set_billboard_mode(StandardMaterial3D::BILLBOARD_FIXED_Y);
	set_pixel_size(0.043);
	set_alpha_cut_mode(SpriteBase3D::ALPHA_CUT_OPAQUE_PREPASS);
	set_draw_flag(SpriteBase3D::FLAG_SHADED, true);
	set_texture_filter(StandardMaterial3D::TEXTURE_FILTER_NEAREST);
}

void SpriteComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_equipped_items", "value"), &SpriteComponent::set_equipped_items);
	ClassDB::bind_method(D_METHOD("get_equipped_items"), &SpriteComponent::get_equipped_items);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "equipped_items", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + ":" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "/" + BaseItem::get_class_static()
		), "set_equipped_items", "get_equipped_items"
	);

	ClassDB::bind_method(D_METHOD("update_layers"), &SpriteComponent::update_layers);
}

void SpriteComponent::_notification(int p_what) {
	switch(p_what) {
	case NOTIFICATION_READY: {
		update_layers();
	};
	case NOTIFICATION_PARENTED: {
		Node *parent = get_parent();
		ERR_FAIL_COND_MSG(
			!parent->is_class(WorldCharacter::get_class_static()),
			"Parent of a SpriteComponent was not a WorldCharacter"
		);

		WorldCharacter *character = cast_to<WorldCharacter>(parent);
		data = character->get_character_data();
		ERR_FAIL_COND_EDMSG(
			data.is_null(),
			"SpriteComponent could not get data from a WorldCharacter who has no CharacterData"
		);

		ERR_FAIL_COND_MSG(
			data->get_species().is_null(),
			"CharacterData is missing a species."
		);
	};
	default:
		break;
	}
}

void SpriteComponent::set_equipped_items(TypedArray<BaseItem> items) {
	equipped_items = items;
	update_equipment();
}

TypedArray<BaseItem> SpriteComponent::get_equipped_items() {
	return equipped_items.duplicate();
}

void SpriteComponent::update_equipment() {
	for(int c_idx = 0; c_idx < char_equip->get_child_count(); c_idx++) {
		char_equip->get_child(c_idx)->queue_free();
	}
	for(Variant item_var : equipped_items) {
		if(item_var.get_type() != Variant::OBJECT) continue;
		Object *item_obj = item_var.operator Object *();
		if(!item_obj->is_class(BaseItem::get_class_static())) continue;
		BaseItem *item = cast_to<BaseItem>(item_obj);
		if(item->get_cosmetic_sprites_dir() == "") continue;

		String cosmetic_dir = item->get_cosmetic_sprites_dir();
		data->get_species();
	}
}

void SpriteComponent::update_layers() {
	for(int c_idx = 0; c_idx < char_layers->get_child_count(); c_idx++)
		char_layers->get_child(c_idx)->queue_free();

	add_layers_from_array(data->get_parts(), data->get_species());
	add_layers_from_array(data->get_patterns(), data->get_species());

	render->set_size(Size2i(64, 24));
	set_texture(render->get_texture());
}

void SpriteComponent::add_layers_from_array(TypedArray<CharacterLayerInfo> layers, Ref<CharacterSpecies> species) {
	for(Variant part_var : layers) {
		if(part_var.get_type() != Variant::OBJECT) continue;
		Object *part_obj = part_var.operator Object *();
		if(!part_obj->is_class(CharacterLayerInfo::get_class_static())) continue;
		CharacterLayerInfo *layer = cast_to<CharacterLayerInfo>(part_obj);

		Ref<SpriteFrames> species_anim_data = species->get_animation_data();

		AnimatedSprite2D *sprite = memnew(AnimatedSprite2D);
		sprite->set_sprite_frames(species_anim_data);
		sprite->set_modulate(layer->get_layer_color());
		sprite->set_centered(false);

		if(species_anim_data->has_animation(layer->get_layer_id() + ":idle"))
			sprite->set_animation(layer->get_layer_id() + ":idle");
		else
			sprite->set_visible(false);
		
		char_layers->add_child(sprite);
		sprite->set_name(layer->get_layer_id());
	}
}