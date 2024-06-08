#include "damage_source.h"

void DamageSource::_bind_methods() {
	ClassDB::add_virtual_method(DamageSource::get_class_static(), MethodInfo(Variant::BOOL, "is_armor_piercing"));
	ClassDB::add_virtual_method(DamageSource::get_class_static(), MethodInfo(Variant::BOOL, "is_unavoidable"));

	ClassDB::bind_method(D_METHOD("set_amount", "value"), &DamageSource::set_amount);
	ClassDB::bind_method(D_METHOD("get_amount"), &DamageSource::get_amount);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount"), "set_amount", "get_amount");
}

DamageSource::DamageSource() {}

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