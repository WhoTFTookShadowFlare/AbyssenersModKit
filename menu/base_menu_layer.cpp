#include "base_menu_layer.h"

BaseMenuLayer::BaseMenuLayer() {}

void BaseMenuLayer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("should_pause"), &BaseMenuLayer::should_pause);
	ClassDB::bind_method(D_METHOD("set_should_pause", "value"), &BaseMenuLayer::set_should_pause);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "should_pause"), "set_should_pause", "should_pause");

	ClassDB::bind_method(D_METHOD("get_can_close_by_button"), &BaseMenuLayer::get_can_close_by_button);
	ClassDB::bind_method(D_METHOD("set_can_close_by_button", "value"), &BaseMenuLayer::set_can_close_by_button);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "can_close_by_button"), "set_can_close_by_button", "get_can_close_by_button");
}

bool BaseMenuLayer::should_pause() {
	return pauses;
}

void BaseMenuLayer::set_should_pause(bool value) {
	pauses = value;
}

bool BaseMenuLayer::get_can_close_by_button() {
	return can_close_by_button;
}

void BaseMenuLayer::set_can_close_by_button(bool value) {
	can_close_by_button = value;
}