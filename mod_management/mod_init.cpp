#include "mod_init.h"

ModInit::ModInit() {}

void ModInit::_bind_methods() {
	ClassDB::add_virtual_method("ModInit", MethodInfo(Variant::PACKED_STRING_ARRAY, "get_dependencies"));
	ClassDB::add_virtual_method("ModInit", MethodInfo("_initialize"));
	ClassDB::add_virtual_method("ModInit", MethodInfo(Variant::PACKED_STRING_ARRAY, "get_load_errors"));
	ClassDB::add_virtual_method("ModInit", MethodInfo(Variant::BOOL, "has_load_error"));
}