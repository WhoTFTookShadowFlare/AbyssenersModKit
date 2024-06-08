#ifndef DAMAGE_SOURCE_H
#define DAMAGE_SOURCE_H

#include "core/io/resource.h"
#include "core/variant/typed_array.h"
#include "core/string/string_name.h"

class DamageSource : public Resource {
	GDCLASS(DamageSource, Resource);
protected:
	static void _bind_methods();
	double amount;
	double orig_amount = 0;

	TypedArray<StringName> flags;

public:
	DamageSource();

	bool has_flag(StringName flag);

	void set_amount(double value);
	double get_amount();

	void set_orig_amount(double value);
	double get_orig_amount();

	void set_flags(TypedArray<StringName> value);
	TypedArray<StringName> get_flags();
};

#endif // DAMAGE_SOURCE_H