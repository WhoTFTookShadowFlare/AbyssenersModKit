#include "save_file.h"

SaveFile::SaveFile() {}

void SaveFile::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_data", "id", "value"), &SaveFile::set_data);
	ClassDB::bind_method(D_METHOD("has_data", "id"), &SaveFile::has_data);
	ClassDB::bind_method(D_METHOD("get_data", "id"), &SaveFile::get_data);

	ClassDB::bind_method(D_METHOD("_set_data_value", "data"), &SaveFile::set_data_value);
	ClassDB::bind_method(D_METHOD("_get_data_value"), &SaveFile::get_data_value);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::DICTIONARY, "data_dictionary",
			PropertyHint::PROPERTY_HINT_NONE, "The data in the file.",
			PropertyUsageFlags::PROPERTY_USAGE_DEFAULT | PropertyUsageFlags::PROPERTY_USAGE_STORE_IF_NULL
		),
		"_set_data_value", "_get_data_value"
	);
}

void SaveFile::set_data(String id, Variant value) {
	data[id] = value;
}

bool SaveFile::has_data(String id) {
	return data.has(id);
}

Variant SaveFile::get_data(String id) {
	return data[id];
}

Variant SaveFile::get_or_default(String id, Variant default_val) {
	if(has_data(id))
		return get_data(id);
	return default_val;
}

void SaveFile::set_data_value(Dictionary data_val) {
	data = data_val;
}

Dictionary SaveFile::get_data_value() {
	return data;
}