#include "base_item.h"

BaseItem::BaseItem() {}

void BaseItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("should_be_removed"), &BaseItem::should_be_removed);

	ClassDB::bind_method(D_METHOD("set_count", "value"), &BaseItem::set_count);
	ClassDB::bind_method(D_METHOD("get_count"), &BaseItem::get_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");

	ClassDB::bind_method(D_METHOD("set_max_count", "value"), &BaseItem::set_max_count);
	ClassDB::bind_method(D_METHOD("get_max_count"), &BaseItem::get_max_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_count"), "set_max_count", "get_max_count");
}

bool BaseItem::should_be_removed() {
	return count <= 0;
}

bool BaseItem::can_merge_with(Ref<BaseItem> other) {
	return other->get_script() == get_script();
}

bool BaseItem::is_max_count() {
	return count >= max_count;
}

void BaseItem::set_count(int value) {
	count = MIN(value, max_count);
}

int BaseItem::get_count() const {
	return count;
}

void BaseItem::set_max_count(int value) {
	max_count = MIN(value, 1);
}

int BaseItem::get_max_count() {
	return max_count;
}