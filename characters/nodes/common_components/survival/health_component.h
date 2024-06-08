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

	double health = 25;
	double max_health = 25;

	WorldCharacter *character;

public:
	HealthComponent();

	void handle_damage(Ref<DamageSource> source);

	void set_health(double value);
	double get_health();

	void set_max_health(double value);
	double get_max_health();

	void heal(double amount);
	void damage(double amount);

	double get_health_pct();

	String get_health_string();
	String get_max_health_string();
};

#endif // HEALTH_COMPONENT_H