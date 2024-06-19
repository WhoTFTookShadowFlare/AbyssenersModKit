#ifndef CONDITION_NEVER_H
#define CONDITION_NEVER_H

#include "base_condition.h"

#include "../../characters/nodes/world_character.h"

class ConditionNever : public BaseCondition {
	GDCLASS(ConditionNever, BaseCondition);
protected:
	static void _bind_methods();
public:
	ConditionNever();

	bool is_met(WorldCharacter *character);
};

#endif // CONDITION_NEVER_H