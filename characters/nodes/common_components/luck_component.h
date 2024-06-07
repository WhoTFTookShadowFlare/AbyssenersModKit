#ifndef LUCK_COMPONENT_H
#define LUCK_COMPONENT_H

#include "scene/main/node.h"
#include "core/math/random_number_generator.h"

class LuckComponent : public Node {
	GDCLASS(LuckComponent, Node);
protected:
	static void _bind_methods();

	RandomNumberGenerator rng;
	real_t luck = 0.0;

public:
	LuckComponent();

	void set_luck(real_t value);
	real_t get_luck();

	real_t get_rand_float(real_t luck_impact = 1.0);
	int64_t get_rand_int(real_t luck_impact = 1.0);
	bool get_rand_bool(real_t luck_impact = 1.0);
};

#endif // LUCK_COMPONENT_H