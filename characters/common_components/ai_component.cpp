#include "ai_component.h"

AIComponent::AIComponent() {
	set_process_mode(RUNNING_PROCESS_MODE);
}

void AIComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("should_run"), &AIComponent::should_run);
}

void AIComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_READY: {
		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		character = cast_to<WorldCharacter>(parent);
	} break;
	default:
		break;
	}
}

WorldCharacter *AIComponent::get_character() {
	if(!character) {
		WARN_PRINT_ONCE("AIComponent does not have the character set, try fetching when processing");
	}
	return character;
}

bool AIComponent::should_run() {
	return true;
}