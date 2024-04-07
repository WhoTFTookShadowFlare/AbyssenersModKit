#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "../../nodes/ai/ai_task.h"

class AIComponent : public AITask {
	GDCLASS(AIComponent, AITask);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	WorldCharacter *character = nullptr;

public:
	AIComponent();

	WorldCharacter *get_character() override;
	bool should_run();
};

#endif // AI_COMPONENT_H