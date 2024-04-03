#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "scene/main/node.h"

#include "core/string/ustring.h"

#include "../../world_character.h"
#include "../../../resources/damage_source.h"

class HealthComponent final : public Node {
	GDCLASS(HealthComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	int64_t health = 25;
	int64_t max_health = 25;

	int64_t regen = 1;
	double time_per_heal = 10.0;
	double next_heal_time = 10.0;

	WorldCharacter *character;

public:
	HealthComponent();

	void handle_damage(Ref<DamageSource> source);

	void set_health(int64_t value);
	int64_t get_health();

	void set_max_health(int64_t value);
	int64_t get_max_health();

	int64_t get_regen();
	void set_regen(int64_t value);

	double get_time_per_heal();
	void set_time_per_heal(double value);

	double get_next_heal_time();
	void set_next_heal_time(double value);

	void heal(int64_t amount);
	void damage(int64_t amount);

	double get_health_pct();

	String get_health_string();
	String get_max_health_string();
};

#endif // HEALTH_COMPONENT_H