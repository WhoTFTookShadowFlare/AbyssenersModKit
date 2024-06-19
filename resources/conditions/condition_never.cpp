#include "condition_never.h"

ConditionNever::ConditionNever() {}

void ConditionNever::_bind_methods() {
	ClassDB::bind_method(D_METHOD("is_met", "character"), &ConditionNever::is_met);
}

bool ConditionNever::is_met(WorldCharacter *character) {
	return false;
}