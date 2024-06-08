#ifndef DAMAGE_SOURCE_H
#define DAMAGE_SOURCE_H

#include "core/io/resource.h"

class DamageSource : public Resource {
	GDCLASS(DamageSource, Resource);
protected:
	static void _bind_methods();
	double amount;
	double orig_amount = 0;

public:
	DamageSource();

	void set_amount(double value);
	double get_amount();

	void set_orig_amount(double value);
	double get_orig_amount();
};

#endif // DAMAGE_SOURCE_H