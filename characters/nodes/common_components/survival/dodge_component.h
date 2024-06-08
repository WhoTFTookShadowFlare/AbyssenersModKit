#ifndef DODGE_COMPONENT_H
#define DODGE_COMPONENT_H

#include "scene/main/node.h"

#include "../../../resources/damage_source.h"
#include "../../world_character.h"

#include "../luck_component.h"

class DodgeComponent : public Node {
	GDCLASS(DodgeComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	double dodge_chance = 0.1;

	double dodge_penalty = 1.0;
	double dodge_penalty_rem = 0.0;

	LuckComponent *luck;

public:
	const StringName NO_DODGE_FLAG = "NO_DODGE_FLAG";

	DodgeComponent();
	void handle_damage(Ref<DamageSource> source);

	void set_dodge_chance(double value);
	double get_dodge_chance();

	void set_dodge_penalty(double value);
	double get_dodge_penalty();

	void set_dodge_penalty_rem(double value);
	double get_dodge_penalty_rem();
};

#endif // DODGE_COMPONENT_H