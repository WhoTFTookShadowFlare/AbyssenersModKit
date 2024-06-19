#include "ai_component.h"


AIComponent::AIComponent() {}

void AIComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_ai_tree", "value"), &AIComponent::set_ai_tree);
	ClassDB::bind_method(D_METHOD("get_ai_tree"), &AIComponent::get_ai_tree);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::OBJECT, "ai_tree",
			PROPERTY_HINT_RESOURCE_TYPE, AITree::get_class_static()
		),
		"set_ai_tree", "get_ai_tree"
	);

	ClassDB::bind_method(D_METHOD("set_ai_tree_path", "value"), &AIComponent::set_ai_tree_path);
	ClassDB::bind_method(D_METHOD("get_ai_tree_path"), &AIComponent::get_ai_tree_path);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "ai_tree_path",
			PROPERTY_HINT_FILE
		),
		"set_ai_tree_path", "get_ai_tree_path"
	);
}

void AIComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
		case NOTIFICATION_READY: {
			ERR_FAIL_COND_MSG(ai_tree.is_null(), "No AITree for an AIComponent");
			ai_tree->load_goals();

			Node *parent = get_parent();
			ERR_FAIL_COND_MSG(!parent->is_class(WorldCharacter::get_class_static()), "Parent of AIComponent is not an WorldCharacter");
			character = cast_to<WorldCharacter>(parent);

			set_physics_process_internal(true);
		}; break;
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
			if(ai_tree.is_null() || character == nullptr) return;
			ai_tree->update(character, get_physics_process_delta_time());
		}; break;
	}
}

void AIComponent::set_ai_tree(Ref<AITree> value) {
	ai_tree = value;
}

Ref<AITree> AIComponent::get_ai_tree() {
	return ai_tree;
}

void AIComponent::set_ai_tree_path(String value) {
	ai_tree_path = value;

	if(Engine::get_singleton()->is_editor_hint()) return;
	ERR_FAIL_COND(!FileAccess::exists(value));
	ResourceLoader loader;
	Ref<Resource> res = loader.load(value);
	ERR_FAIL_COND(!res->is_class(AITree::get_class_static()));
	ai_tree = Ref<AITree>(cast_to<AITree>(res.ptr()));
}

String AIComponent::get_ai_tree_path() {
	return ai_tree_path;
}