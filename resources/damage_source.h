#ifndef DAMAGE_SOURCE_H
#define DAMAGE_SOURCE_H

#include "core/io/resource.h"

class DamageSource : public Resource {
	GDCLASS(DamageSource, Resource);
protected:
	static void _bind_methods();
	u_int64_t amount;
	u_int64_t orig_amount = 0;

public:
	DamageSource();

	void set_amount(u_int64_t value);
	u_int64_t get_amount();

	void set_orig_amount(u_int64_t value);
	u_int64_t get_orig_amount();
};

#endif // DAMAGE_SOURCE_H