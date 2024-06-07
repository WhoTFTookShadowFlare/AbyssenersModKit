#ifndef AI_TASK_H
#define AI_TASK_H

#include "scene/main/node.h"

#include "../world_character.h"

class AITask : public Node {
	GDCLASS(AITask, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);
public:
	const Node::ProcessMode RUNNING_PROCESS_MODE = PROCESS_MODE_PAUSABLE;
	const Node::ProcessMode STOPED_PROCESS_MODE = PROCESS_MODE_DISABLED;

	AITask();

	virtual WorldCharacter *get_character();

	bool is_running();
	void update_run_state();
};

#endif // AI_TASK_H