#include "stat_modifier.h"

StatModifier::StatModifier() {}

void StatModifier::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_target_component"), &StatModifier::get_target_component);
	ClassDB::bind_method(D_METHOD("get_target_property"), &StatModifier::get_target_property);

	ClassDB::bind_method(D_METHOD("set_target_stat", "value"), &StatModifier::set_target_stat);
	ClassDB::bind_method(D_METHOD("get_target_stat"), &StatModifier::get_target_stat);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "target_stat"), "set_target_stat", "get_target_stat");

	ClassDB::bind_method(D_METHOD("set_multiplicitive", "value"), &StatModifier::set_mulitplicitive);
	ClassDB::bind_method(D_METHOD("is_multiplicitive"), &StatModifier::is_multiplicitive);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "multiplicitive"), "set_multiplicitive", "is_multiplicitive");

	ClassDB::bind_method(D_METHOD("set_change", "value"), &StatModifier::set_change);
	ClassDB::bind_method(D_METHOD("get_change"), &StatModifier::get_change);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "change"), "set_change", "get_change");

	ClassDB::bind_method(D_METHOD("equals", "other"), &StatModifier::equals);
}

String StatModifier::get_target_component() {
	return target_stat.substr(0, target_stat.find_char(':'));
}

String StatModifier::get_target_property() {
	return target_stat.substr(target_stat.find_char(':') + 1);
}

void StatModifier::set_target_stat(String value) {
	target_stat = value;
}

String StatModifier::get_target_stat() {
	return target_stat;
}

void StatModifier::set_mulitplicitive(bool value) {
	multiplicitive = value;
}

bool StatModifier::is_multiplicitive() {
	return multiplicitive;
}

void StatModifier::set_change(double value) {
	change = value;
}

double StatModifier::get_change() {
	return change;
}

bool StatModifier::equals(Ref<StatModifier> RHS) {
	return	target_stat == RHS->target_stat &&
			multiplicitive == RHS->multiplicitive &&
			change == RHS->change;
}