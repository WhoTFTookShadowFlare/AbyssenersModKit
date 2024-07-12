#include "damage_source.h"

#include "../nodes/world_character.h"

#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

void DamageSource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_flags", "flags"), &DamageSource::set_flags);
	ClassDB::bind_method(D_METHOD("get_flags"), &DamageSource::get_flags);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "flags", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::STRING_NAME)
		),
		"set_flags", "get_flags"
	);

	ClassDB::bind_method(D_METHOD("set_amount", "value"), &DamageSource::set_amount);
	ClassDB::bind_method(D_METHOD("get_amount"), &DamageSource::get_amount);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount"), "set_amount", "get_amount");

	ClassDB::bind_method(D_METHOD("set_causing_char", "who"), &DamageSource::set_causing_char);
	ClassDB::bind_method(D_METHOD("get_causing_char"), &DamageSource::get_causing_char);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::OBJECT, "causing_char",
			PROPERTY_HINT_RESOURCE_TYPE, WorldCharacter::get_class_static()
		),
		"set_causing_char", "get_causing_char"
	);
}

DamageSource::DamageSource() {}

bool DamageSource::has_flag(StringName flag) {
	return flags.has(flag);
}

void DamageSource::set_amount(double value) {
	amount = value;
}

double DamageSource::get_amount() {
	return amount;
}

void DamageSource::set_orig_amount(double value) {
	ERR_FAIL_COND(orig_amount > 0);
	orig_amount = value;
	amount = value;
}

double DamageSource::get_orig_amount() {
	return orig_amount;
}

void DamageSource::set_flags(TypedArray<StringName> value) {
	flags = value;
}

TypedArray<StringName> DamageSource::get_flags() {
	return flags;
}

void DamageSource::set_causing_char(WorldCharacter *value) {
	causing_char_path = value->get_path();
}

WorldCharacter *DamageSource::get_causing_char() {
	Node *target = SceneTree::get_singleton()->get_root()->get_node(causing_char_path);
	ERR_FAIL_COND_V_MSG(target == nullptr, nullptr, "Character path is no longer valid, returning null");
	ERR_FAIL_COND_V_MSG(!target->is_class(WorldCharacter::get_class_static()), nullptr, "Path on DamageSource source character is not a WorldCharacter");
	return cast_to<WorldCharacter>(target);
}