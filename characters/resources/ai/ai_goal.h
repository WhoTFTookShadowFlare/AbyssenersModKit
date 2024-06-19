#ifndef AI_GOAL_H
#define AI_GOAL_H

#include "core/io/resource.h"
#include "core/variant/typed_array.h"

#include "../../../resources/conditions/base_condition.h"
#include "../../nodes/world_character.h"

class AIGoal : public Resource {
	GDCLASS(AIGoal, Resource);
protected:
	static void _bind_methods();

	String start_condition_directory;
	String update_condition_directory;

	TypedArray<BaseCondition> start_conditions;
	TypedArray<BaseCondition> update_conditions;

	String sub_goal_directory;
	TypedArray<AIGoal> sub_goals;

	bool done_loading = false;
public:
	AIGoal();
	
	void set_start_condition_directory(String value);
	String get_start_condition_directory();

	void set_update_condition_directory(String value);
	String get_update_condition_directory();

	void set_sub_goal_directory(String value);
	String get_sub_goal_directory();

	void load_data();
	bool is_loaded();

	bool can_start(WorldCharacter *character);
	bool can_update(WorldCharacter *character);

	void update_subgoals(WorldCharacter *character, double delta);
};

#endif // AI_GOAL_H