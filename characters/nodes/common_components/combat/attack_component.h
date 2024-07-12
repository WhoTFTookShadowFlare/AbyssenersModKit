#ifndef ATTACK_COMPONENT_H
#define ATTACK_COMPONENT_H

#include "scene/main/node.h"

#include "../../world_character.h"
#include "../../../../resources/base_item.h"

class AttackComponent : public Node {
	GDCLASS(AttackComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	float attack_rate = 1.0;

	Vector3 atk_dir;
	float atk_dist = 1.0;
	Ref<BaseItem> equiped_item;

	WorldCharacter *character;

public:
	AttackComponent();

	void set_attack_rate(float value);
	float get_attack_rate();

	void set_atk_dir(Vector3 value);
	Vector3 get_atk_dir();

	void set_atk_dist(float value);
	float get_atk_dist();

	void set_equiped_item(Ref<BaseItem> value);
	Ref<BaseItem> get_equiped_item();
};

#endif // ATTACK_COMPONENT_H