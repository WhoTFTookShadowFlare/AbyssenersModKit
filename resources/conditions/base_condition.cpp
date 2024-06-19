#include "base_condition.h"

#include "../../characters/nodes/world_character.h"

BaseCondition::BaseCondition() {}

void BaseCondition::_bind_methods() {
	ClassDB::add_virtual_method(
		BaseCondition::get_class_static(), 
		MethodInfo(
			Variant::BOOL, "is_met",
			PropertyInfo(
				Variant::OBJECT, "character",
				PROPERTY_HINT_NODE_TYPE, WorldCharacter::get_class_static()
			)
		)
	);
}