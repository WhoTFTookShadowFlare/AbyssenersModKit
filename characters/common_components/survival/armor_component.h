#ifndef ARMOR_COMPONENT_H
#define ARMOR_COMPONENT_H

#include "scene/main/node.h"

#include "../../world_character.h"
#include "../../../resources/damage_source.h"

class ArmorComponent final : public Node {
	GDCLASS(ArmorComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	int64_t armor = 25;
	int64_t max_armor = 25;

	double gen_hit_delay = 10.0;
	double gen_tick_rate = 1.0; // if 0, always be max after hit delay.

	double next_gen_tick = 1.0;
	double gen_pct = 0.15; // rounded down, min 1

	double armor_effeciency = 0.80;

	WorldCharacter *character;

public:
	ArmorComponent();

	void handle_damage(Ref<DamageSource> source);

	void set_armor(int64_t value);
	int64_t get_armor();

	void set_max_armor(int64_t value);
	int64_t get_max_armor();

	double get_armor_pct();
	double get_tank_pct();

	void repair(int64_t amount);
	void damage(int64_t amount);

	void set_gen_hit_delay(double value);
	double get_gen_hit_delay();

	void set_gen_tick_rate(double value);
	double get_gen_tick_rate();

	void set_next_gen_tick(double value);
	double get_next_gen_tick();

	void set_generated_pct(double value);
	double get_generated_pct();

	void set_armor_effeciency(double value);
	double get_armor_effeciency();
};

#endif // ARMOR_COMPONENT_H