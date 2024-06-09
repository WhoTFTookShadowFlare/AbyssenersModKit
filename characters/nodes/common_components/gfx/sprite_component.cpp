#include "sprite_component.h"

#include "../../world_character.h"

SpriteComponent::SpriteComponent() {}

void SpriteComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_item", "item"), &SpriteComponent::add_item);
	ClassDB::bind_method(D_METHOD("remove_item", "item"), &SpriteComponent::remove_item);
}

void SpriteComponent::_notification(int p_what) {
	switch(p_what) {
	case NOTIFICATION_READY: {
		render = memnew(SubViewport);
		add_child(render);
		render_texture = Ref<ViewportTexture>(memnew(ViewportTexture));
		render_texture->set_viewport_path_in_scene(render->get_path());
		set_texture(render_texture);

		char_parts = memnew(Node2D);
		render->add_child(char_parts);

		char_equip = memnew(Node2D);
		render->add_child(char_equip);
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
	};
	default:
		break;
	}
}

void SpriteComponent::add_item(Ref<BaseItem> item) {
	equiped_items.append(item);
	update_equipment();
}

void SpriteComponent::remove_item(Ref<BaseItem> item) {
	equiped_items.erase(item);
	update_equipment();
}

void SpriteComponent::update_equipment() {
	for(int c_idx = 0; c_idx < char_equip->get_child_count(); c_idx++) {
		char_equip->get_child(c_idx)->queue_free();
	}
	for(Variant item_var : equiped_items) {
		if(item_var.get_type() != Variant::OBJECT) continue;
		Object *item_obj = item_var.operator Object *();
		if(!item_obj->is_class(BaseItem::get_class_static())) continue;
		BaseItem *item = cast_to<BaseItem>(item_obj);
		if(item->get_cosmetic_sprites_dir() == "") continue;

		String cosmetic_dir = item->get_cosmetic_sprites_dir();
		data->get_species();
	}
}