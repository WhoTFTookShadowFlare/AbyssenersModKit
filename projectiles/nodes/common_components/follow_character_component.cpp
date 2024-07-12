#include "follow_character_component.h"

#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

FollowCharacterComponent::FollowCharacterComponent() {}

void FollowCharacterComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_target_character", "value"), &FollowCharacterComponent::set_target_character);
	ClassDB::bind_method(D_METHOD("get_target_character"), &FollowCharacterComponent::get_target_character);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::OBJECT, "target_character",
			PROPERTY_HINT_RESOURCE_TYPE, WorldCharacter::get_class_static(),
			PROPERTY_USAGE_EDITOR
		),
		"set_target_character", "get_target_character"
	);

	ClassDB::bind_method(D_METHOD("set_target_character_path", "value"), &FollowCharacterComponent::set_target_character_path);
	ClassDB::bind_method(D_METHOD("get_target_character_path"), &FollowCharacterComponent::get_target_character_path);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::NODE_PATH, "target_character_path"
		),
		"set_target_character_path", "get_target_character_path"
	);

	ClassDB::bind_method(D_METHOD("set_offset", "value"), &FollowCharacterComponent::set_offset);
	ClassDB::bind_method(D_METHOD("get_offset"), &FollowCharacterComponent::get_offset);
	ADD_PROPERTY(
		PropertyInfo(Variant::VECTOR3, "offset"),
		"set_offset", "get_offset"
	);
}

void FollowCharacterComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
		case NOTIFICATION_READY: {
			Node *parent = get_parent();
			ERR_FAIL_COND_MSG(!parent->is_class(Projectile::get_class_static()), "Parent of FollowCharacterComponent was not a Projectile");
			projectile = cast_to<Projectile>(parent);
			set_physics_process_internal(true);
		}; break;
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
			if(target_char == nullptr) return;
			projectile->set_position(target_char->get_position() + offset);
		}; break;
	}
}

void FollowCharacterComponent::set_target_character_path(NodePath value) {
Node *t_node = SceneTree::get_singleton()->get_root()->get_node(value);
	ERR_FAIL_COND_MSG(t_node == nullptr, "No character at: " + value);
	ERR_FAIL_COND_MSG(!t_node->is_class(WorldCharacter::get_class_static()), "Path was not to a WorldCharacter");
	target_char = cast_to<WorldCharacter>(t_node);
	target = value;
}

NodePath FollowCharacterComponent::get_target_character_path() {
	return target;
}

void FollowCharacterComponent::set_target_character(WorldCharacter *value) {
	target_char = value;
	target = value->get_path();
}

WorldCharacter *FollowCharacterComponent::get_target_character() {
	return target_char;
}

void FollowCharacterComponent::set_offset(Vector3 value) {
	offset = value;
}

Vector3 FollowCharacterComponent::get_offset() {
	return offset;
}
