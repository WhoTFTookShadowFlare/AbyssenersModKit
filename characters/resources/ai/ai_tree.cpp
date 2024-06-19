#include "ai_tree.h"

#include "core/io/dir_access.h"

AITree::AITree() {}

void AITree::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_goals"), &AITree::load_goals);
	ClassDB::bind_method(D_METHOD("is_loaded"), &AITree::is_loaded);

	ClassDB::bind_method(D_METHOD("force_end_goal"), &AITree::force_end_goal);

	ClassDB::bind_method(D_METHOD("set_goal_directory", "directory"), &AITree::set_goal_directory);
	ClassDB::bind_method(D_METHOD("get_goal_directory"), &AITree::get_goal_directory);
	ADD_PROPERTY(
		PropertyInfo(Variant::STRING, "goal_directory", PROPERTY_HINT_DIR),
		"set_goal_directory", "get_goal_directory"
	);

	ClassDB::bind_method(D_METHOD("update", "who", "delta"), &AITree::update);
}

void AITree::load_goals() {
	if(is_loaded()) return;
	ERR_FAIL_COND_MSG(!DirAccess::dir_exists_absolute(goal_directory), "Missing AITree goal_directory: " + goal_directory);

	Ref<DirAccess> dir = DirAccess::open(goal_directory);
	ResourceLoader loader;
	for(String file_name : dir->get_files()) {
		Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file_name);
		ERR_CONTINUE(res.is_null());
		ERR_CONTINUE_MSG(!res->is_class(AIGoal::get_class_static()), "File '" + file_name + "' should be an AIGoal");
		AIGoal *goal = cast_to<AIGoal>(res.ptr());
		goal->load_data();
		goals.append(goal);
	}

	has_loaded_goals = true;
}

bool AITree::is_loaded() {
	return has_loaded_goals;
}

void AITree::force_end_goal() {
	current_goal = Ref<AIGoal>();
}

void AITree::set_goal_directory(String value) {
	goal_directory = value;
}

String AITree::get_goal_directory() {
	return goal_directory;
}

TypedArray<AIGoal> AITree::get_goals() {
	return goals.duplicate();
}

TypedArray<AIGoal> AITree::get_startable_goals(WorldCharacter *character) {
	TypedArray<AIGoal> startable;
	for(Variant var : goals) {
		ERR_CONTINUE_MSG(var.get_type() != Variant::OBJECT, "An entry in goals was not an object");
		Object *obj = var.operator Object *();
		ERR_CONTINUE_MSG(!obj->is_class(AIGoal::get_class_static()), "An entry in goals was not an AIGoal");
		AIGoal *goal = cast_to<AIGoal>(obj);
		if(goal->can_start(character)) startable.push_back(goal);
	}
	return startable;
}

void AITree::update(WorldCharacter *who, double delta) {
	if(current_goal.is_null()) {
		current_goal = get_startable_goals(who).pick_random();
		if(current_goal.is_null()) return;
		current_goal->emit_signal("on_start", who);
	}


	if(current_goal->can_update(who)) {
		current_goal->emit_signal("on_update", who, delta);
	} else {
		current_goal->emit_signal("on_stop", who);
		current_goal = Ref<AIGoal>();
	}
}