#ifndef AI_TREE_H
#define AI_TREE_H

#include "core/io/resource.h"
#include "core/variant/typed_array.h"

#include "ai_goal.h"

#include "../../nodes/world_character.h"

class AITree : public Resource {
	GDCLASS(AITree, Resource);
protected:
	static void _bind_methods();

	TypedArray<AIGoal> goals;
	Ref<AIGoal> current_goal = Ref<AIGoal>();

	String goal_directory;

	bool has_loaded_goals = false;
public:
	AITree();

	void load_goals();
	bool is_loaded();

	void force_end_goal();

	void set_goal_directory(String value);
	String get_goal_directory();

	TypedArray<AIGoal> get_goals();
	TypedArray<AIGoal> get_startable_goals(WorldCharacter *character);

	void update(WorldCharacter *who, double delta);
};

#endif // AI_TREE_H