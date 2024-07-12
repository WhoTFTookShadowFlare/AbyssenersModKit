#include "base_item.h"

#include "scene/resources/texture.h"

#include "../characters/nodes/world_character.h"

#include "../projectiles/nodes/projectile.h"

BaseItem::BaseItem() {}

void BaseItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("should_be_removed"), &BaseItem::should_be_removed);

	ClassDB::bind_method(D_METHOD("set_count", "value"), &BaseItem::set_count);
	ClassDB::bind_method(D_METHOD("get_count"), &BaseItem::get_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");

	ClassDB::bind_method(D_METHOD("set_max_count", "value"), &BaseItem::set_max_count);
	ClassDB::bind_method(D_METHOD("get_max_count"), &BaseItem::get_max_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_count"), "set_max_count", "get_max_count");

	ClassDB::add_virtual_method(BaseItem::get_class_static(), MethodInfo(PropertyInfo(Texture2D::get_class_static()), "get_item_icon"));
	ClassDB::add_virtual_method(
		BaseItem::get_class_static(),
		MethodInfo(
			PropertyInfo(
				Variant::ARRAY, "ret", PROPERTY_HINT_ARRAY_TYPE,
				String::num(Variant::STRING) + ":"
			), "get_custom_item_signal_names"
		)
	);

	ClassDB::bind_method(D_METHOD("set_cosmetic_sprites_dir", "location"), &BaseItem::set_cosmetic_sprites_dir);
	ClassDB::bind_method(D_METHOD("get_cosmetic_sprites_dir"), &BaseItem::get_cosmetic_sprites_dir);
	ADD_PROPERTY(
		PropertyInfo(Variant::STRING, "cosmetic_sprites_dir", PROPERTY_HINT_DIR),
		"set_cosmetic_sprites_dir", "get_cosmetic_sprites_dir"
	);

	ADD_SIGNAL(MethodInfo(
		Variant::NIL, "on_consume",
		PropertyInfo(
			Variant::OBJECT, "who",
			PROPERTY_HINT_NODE_TYPE, WorldCharacter::get_class_static()
		)
	));

	ClassDB::bind_method(D_METHOD("get_item_signal_names"), &BaseItem::get_item_signal_names);

	ClassDB::add_virtual_method(get_class_static(), 
		MethodInfo(
			PropertyInfo(
				Variant::OBJECT, "projectile",
				PROPERTY_HINT_RESOURCE_TYPE, Projectile::get_class_static()
			),
			"get_projectile",
			PropertyInfo(
				Variant::OBJECT, "who",
				PROPERTY_HINT_RESOURCE_TYPE, WorldCharacter::get_class_static()
			)
		)
	);
}

bool BaseItem::should_be_removed() {
	return count <= 0;
}

bool BaseItem::can_merge_with(Ref<BaseItem> other) {
	return other->get_script() == get_script();
}

bool BaseItem::is_max_count() {
	return count >= max_count;
}

void BaseItem::set_weight(float value) {
	weight = MIN(0.0, value);
}

float BaseItem::get_weight() {
	return weight;
}

void BaseItem::set_count(int value) {
	count = MIN(value, max_count);
}

int BaseItem::get_count() const {
	return count;
}

void BaseItem::set_max_count(int value) {
	max_count = MIN(value, 1);
}

int BaseItem::get_max_count() {
	return max_count;
}

void BaseItem::set_cosmetic_sprites_dir(String location) {
	cosmetic_sprites_dir = location;
}

String BaseItem::get_cosmetic_sprites_dir() {
	return cosmetic_sprites_dir;
}

TypedArray<String> BaseItem::get_item_signal_names() {
	TypedArray<String> signals;
	
	Variant res = call("get_custom_item_signals");
	if(res.get_type() == Variant::ARRAY) {
		Array arr = res.operator Array();
		for(Variant var : arr) {
			if(var.get_type() == Variant::STRING) {
				signals.push_back(var.operator String());
			}
		}
	}

	signals.push_back("on_consume");

	return signals;
}