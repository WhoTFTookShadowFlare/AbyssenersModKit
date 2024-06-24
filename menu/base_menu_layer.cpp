#include "base_menu_layer.h"

BaseMenuLayer::BaseMenuLayer() {}

void BaseMenuLayer::_bind_methods() {
	ClassDB::add_virtual_method(BaseMenuLayer::get_class_static(), MethodInfo(Variant::BOOL, "should_pause"));
	ClassDB::add_virtual_method(BaseMenuLayer::get_class_static(), MethodInfo(Variant::BOOL, "can_close"));

	ADD_SIGNAL(MethodInfo(Variant::NIL, "became_top_layer"));
	ADD_SIGNAL(MethodInfo(Variant::NIL, "no_longer_top_layer"));
}