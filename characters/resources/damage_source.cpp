#include "damage_source.h"

void DamageSource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_flags", "flags"), &DamageSource::set_flags);
	ClassDB::bind_method(D_METHOD("get_flags"), &DamageSource::get_flags);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "flags", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::STRING_NAME)
		),
		"set_flags", "get_flags"
	);

	ClassDB::bind_method(D_METHOD("set_amount", "value"), &DamageSource::set_amount);
	ClassDB::bind_method(D_METHOD("get_amount"), &DamageSource::get_amount);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount"), "set_amount", "get_amount");
}

DamageSource::DamageSource() {}

bool DamageSource::has_flag(StringName flag) {
	return flags.has(flag);
}

void DamageSource::set_amount(double value) {
	amount = value;
}

double DamageSource::get_amount() {
	return amount;
}

void DamageSource::set_orig_amount(double value) {
	ERR_FAIL_COND(orig_amount > 0);
	orig_amount = value;
	amount = value;
}

double DamageSource::get_orig_amount() {
	return orig_amount;
}

void DamageSource::set_flags(TypedArray<StringName> value) {
	flags = value;
}

TypedArray<StringName> DamageSource::get_flags() {
	return flags;
}