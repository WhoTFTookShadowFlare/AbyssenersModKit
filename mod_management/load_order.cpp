#include "load_order.h"

#include "core/io/file_access.h"

LoadOrder::LoadOrder() {}

void LoadOrder::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_list", "list"), &LoadOrder::set_list);
	ClassDB::bind_method(D_METHOD("get_list"), &LoadOrder::get_list);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "orderr_list"), "set_list", "get_list");
}

void LoadOrder::swap(int a, int b) {
	String b_val = order_list[b];
	order_list[b] = order_list[a];
	order_list[a] = b_val;
}

void LoadOrder::add(String file) {
	ERR_FAIL_COND_MSG(!FileAccess::exists("user://mods/" + file + ".pck"), "Missing " + file);
	order_list.append(file);
}

void LoadOrder::remove(String file) {
	ERR_FAIL_COND_MSG(!order_list.has(file), file + " was not found in the current load order");
	order_list.erase(file);
}

void LoadOrder::set_list(TypedArray<String> list) {
	order_list = list;
}

TypedArray<String> LoadOrder::get_list() {
	return order_list;
}