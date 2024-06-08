#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

#include "core/io/resource.h"

class StatModifier : public Resource {
	GDCLASS(StatModifier, Resource);
protected:
	static void _bind_methods();

	// As "ComponentClass:Property"
	String target_stat;
	bool multiplicitive = false;
	double change;

public:
	StatModifier();

	String get_target_component();
	String get_target_property();

	void set_target_stat(String value);
	String get_target_stat();

	void set_mulitplicitive(bool value);
	bool is_multiplicitive();

	void set_change(double value);
	double get_change();

	bool equals(Ref<StatModifier> RHS);
};

#endif // STAT_MODIFIER_H