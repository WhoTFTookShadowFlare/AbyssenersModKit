#include "ai_goal.h"

#include "../../nodes/world_character.h"

#include "core/io/dir_access.h"

AIGoal::AIGoal() {}

void AIGoal::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_start_condition_directory", "value"), &AIGoal::set_start_condition_directory);
	ClassDB::bind_method(D_METHOD("get_start_condition_directory"), &AIGoal::get_start_condition_directory);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "start_condition_directory",
			PROPERTY_HINT_DIR
		),
		"set_start_condition_directory", "get_start_condition_directory"
	);

	ClassDB::bind_method(D_METHOD("set_update_condition_directory", "value"), &AIGoal::set_update_condition_directory);
	ClassDB::bind_method(D_METHOD("get_update_condition_directory"), &AIGoal::get_update_condition_directory);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "update_condition_directory",
			PROPERTY_HINT_DIR
		),
		"set_update_condition_directory", "get_update_condition_directory"
	);

	ClassDB::bind_method(D_METHOD("set_sub_goal_directory", "value"), &AIGoal::set_sub_goal_directory);
	ClassDB::bind_method(D_METHOD("get_sub_goal_directory"), &AIGoal::get_sub_goal_directory);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING, "sub_goal_directory",
			PROPERTY_HINT_DIR
		),
		"set_sub_goal_directory", "get_sub_goal_directory"
	);

	ClassDB::bind_method(D_METHOD("load_data"), &AIGoal::load_data);
	ClassDB::bind_method(D_METHOD("is_loaded"), &AIGoal::is_loaded);

	ClassDB::bind_method(D_METHOD("update_subgoals", "character", "delta"), &AIGoal::update_subgoals);

	ADD_SIGNAL(MethodInfo(
		Variant::NIL, "on_start", 
		PropertyInfo(
			Variant::OBJECT, "who",
			PROPERTY_HINT_NODE_TYPE, WorldCharacter::get_class_static()
		)
	));

	ADD_SIGNAL(MethodInfo(
		Variant::NIL, "on_update",
		PropertyInfo(
			Variant::OBJECT, "who",
			PROPERTY_HINT_NODE_TYPE, WorldCharacter::get_class_static()
		),
		PropertyInfo(Variant::FLOAT, "delta")
	));

	ADD_SIGNAL(MethodInfo(
		Variant::NIL, "on_stop",
		PropertyInfo(
			Variant::OBJECT, "who",
			PROPERTY_HINT_NODE_TYPE, WorldCharacter::get_class_static()
		)
	));
}

void AIGoal::set_start_condition_directory(String value) {
	start_condition_directory = value;
}

String AIGoal::get_start_condition_directory() {
	return start_condition_directory;
}

void AIGoal::set_update_condition_directory(String value) {
	update_condition_directory = value;
}

String AIGoal::get_update_condition_directory() {
	return update_condition_directory;
}

void AIGoal::set_sub_goal_directory(String value) {
	sub_goal_directory = value;
}

String AIGoal::get_sub_goal_directory() {
	return sub_goal_directory;
}

void AIGoal::load_data() {
	if(is_loaded()) return;

	ResourceLoader loader;
	if(start_condition_directory != "") {
		Ref<DirAccess> dir = DirAccess::open(start_condition_directory);
		ERR_FAIL_COND(dir.is_null());
		for(String file_name : dir->get_files()) {
			Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file_name);
			ERR_CONTINUE_MSG(!res->is_class(BaseCondition::get_class_static()), file_name + " was not a condition");
			start_conditions.push_back(cast_to<BaseCondition>(res.ptr()));
		}
	}

	if(update_condition_directory != "") {
		Ref<DirAccess> dir = DirAccess::open(update_condition_directory);
		ERR_FAIL_COND(dir.is_null());
		for(String file_name : dir->get_files()) {
			Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file_name);
			ERR_CONTINUE_MSG(!res->is_class(BaseCondition::get_class_static()), file_name + " was not a condition");
			update_conditions.push_back(cast_to<BaseCondition>(res.ptr()));
		}
	}

	if(sub_goal_directory != "") {
		Ref<DirAccess> dir = DirAccess::open(sub_goal_directory);
		ERR_FAIL_COND(dir.is_null());
		for(String file_name : dir->get_files()) {
			Ref<Resource> res = loader.load(dir->get_current_dir() + '/' + file_name);
			ERR_CONTINUE_MSG(!res->is_class(AIGoal::get_class_static()), " was not a AIGoal");
			AIGoal *sub_goal = cast_to<AIGoal>(res.ptr());
			sub_goal->load_data();
			sub_goals.push_back(sub_goal);
		}
	}

	done_loading = true;
	connect("on_update", Callable(this, "update_subgoals"));
}

bool AIGoal::can_start(WorldCharacter *character) {
	for(Variant var : start_conditions) {
		ERR_CONTINUE_MSG(var.get_type() != Variant::OBJECT, "an update condition was not an object");
		Object *obj = var.operator Object *();
		ERR_CONTINUE_MSG(!obj->is_class(BaseCondition::get_class_static()), "an update condition was not a BaseCondition derivitive");
		BaseCondition *cond = cast_to<BaseCondition>(obj);
		if(!cond->call("is_met", character)) return false;
	}
	return true;
}

bool AIGoal::can_update(WorldCharacter *character) {
	for(Variant var : update_conditions) {
		ERR_CONTINUE_MSG(var.get_type() != Variant::OBJECT, "an update condition was not an object");
		Object *obj = var.operator Object *();
		ERR_CONTINUE_MSG(!obj->is_class(BaseCondition::get_class_static()), "an update condition was not a BaseCondition derivitive");
		BaseCondition *cond = cast_to<BaseCondition>(obj);
		if(!cond->call("is_met", character)) return false;
	}
	return true;
}

bool AIGoal::is_loaded() {
	return done_loading;
}

void AIGoal::update_subgoals(WorldCharacter *character, double delta) {
	
}