#include "ai_task.h"

AITask::AITask() {
	set_process_mode(STOPED_PROCESS_MODE);
}

void AITask::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_character"), &AITask::get_character);

	ClassDB::add_virtual_method(AITask::get_class_static(), MethodInfo(Variant::BOOL, "should_run"));

	ADD_SIGNAL(MethodInfo("on_start"));
	ADD_SIGNAL(MethodInfo("on_stop"));
}

void AITask::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_READY: {
		set_physics_process_internal(true);
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		bool running = is_running();

		if(running) {
			for(int c_idx = 0; c_idx < get_child_count(); c_idx++) {
				Node *child = get_child(c_idx);
				ERR_CONTINUE_MSG(!child->is_class(AITask::get_class_static()), "A child AITask was not an AITask!");
				AITask *task = cast_to<AITask>(child);
				task->update_run_state();
			}
		}

		update_run_state();
	} break;
	default:
		break;
	}
}

WorldCharacter *AITask::get_character() {
	if(!get_parent()) return nullptr;
	Node *parent = get_parent();
	if(!parent->is_class(AITask::get_class_static())) {
		_err_print_error(FUNCTION_STR, __FILE__, __LINE__, "Condition \"" _STR(!parent->is_class(AITask::get_class_static())) "\" is true.");
		return nullptr;
	}
	AITask *parent_task = cast_to<AITask>(parent);
	return parent_task->get_character();
}

bool AITask::is_running() {
	return get_process_mode() == RUNNING_PROCESS_MODE;
}

void AITask::update_run_state() {
	bool running = is_running();
	bool should = call("should_run").booleanize();

	if((running && should) || (!running && !should)) return;
	if(running) {
		set_process_mode(STOPED_PROCESS_MODE);
		emit_signal("on_stop");
	} else {
		set_process_mode(RUNNING_PROCESS_MODE);
		emit_signal("on_start");
	}
}