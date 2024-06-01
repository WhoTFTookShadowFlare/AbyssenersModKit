#include "inventory_component.h"

InventoryComponent::InventoryComponent() {}

void InventoryComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("can_add", "item"), &InventoryComponent::can_add);
	ClassDB::bind_method(D_METHOD("add_item", "item"), &InventoryComponent::add_item);

	ClassDB::bind_method(D_METHOD("has_item", "item_type"), &InventoryComponent::has_item);
	ClassDB::bind_method(D_METHOD("get_item", "item_type"), &InventoryComponent::get_item);
	ClassDB::bind_method(D_METHOD("remove_item", "item_type"), &InventoryComponent::remove_item);

	ClassDB::bind_method(D_METHOD("set_item_limit", "value"), &InventoryComponent::set_item_limit);
	ClassDB::bind_method(D_METHOD("get_item_limit"), &InventoryComponent::get_item_limit);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_limit"), "set_item_limit", "get_item_limit");

	ClassDB::bind_method(D_METHOD("set_contents", "value"), &InventoryComponent::set_contents);
	ClassDB::bind_method(D_METHOD("get_contents"), &InventoryComponent::get_contents);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::ARRAY, "contents", PROPERTY_HINT_ARRAY_TYPE,
			String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":" + BaseItem::get_class_static()
		), "set_contents", "get_contents"
	);

	ClassDB::bind_method(D_METHOD("filter_fn", "entry"), &InventoryComponent::filter_fn);
	ClassDB::bind_method(D_METHOD("clean_empty"), &InventoryComponent::clean_empty);

	ADD_SIGNAL(MethodInfo(Variant::NIL, "inventory_updated"));
}

bool InventoryComponent::can_add(Ref<BaseItem> item) {
	if(contents.size() >= item_limit && !has_item(item->get_script())) return false;
	if(has_item(item->get_script())) {
		Ref<BaseItem> already = get_item(item->get_script());
		if(already->get_count() >= already->get_max_count()) return false;
	}
	return true;
}

void InventoryComponent::add_item(Ref<BaseItem> item) {
	if(!can_add(item)) return;

	if(has_item(item->get_script())) {
		Ref<BaseItem> already = get_item(item->get_script());
		int max = item->get_max_count();
		int total = already->get_count() + item->get_count();
		item->set_count(total - max);
		already->set_count(MIN(max, total));
	} else {
		contents.push_back(item);
	}
	emit_signal("inventory_updated");
}

bool InventoryComponent::has_item(Ref<Script> item_type) {
	return get_item(item_type).is_valid();
}

Ref<BaseItem> InventoryComponent::get_item(Ref<Script> item_type) {
	for(int idx = 0; idx < contents.size(); idx++) {
		Variant var = contents[idx];
		if(var.get_type() == Variant::OBJECT) {
			if(var.operator Object *()->get_script() == item_type) return cast_to<BaseItem>(var);
		}
	}
	return Ref<BaseItem>();
}

void InventoryComponent::remove_item(Ref<Script> item_type) {
	Ref<BaseItem> item = get_item(item_type);
	contents.erase(item);
	emit_signal("inventory_updated");
}

bool InventoryComponent::filter_fn(Variant entry) {
	if(!entry.is_ref_counted()) return false;
	if(!(entry.operator Object *())->is_class(BaseItem::get_class_static())) return false;
	return cast_to<BaseItem>(entry.operator Object *())->get_count() > 0;
}

void InventoryComponent::clean_empty() {
	contents.filter(Callable(this, "filter_fn"));
	emit_signal("inventory_updated");
}

void InventoryComponent::set_item_limit(int value) {
	item_limit = value;
}

int InventoryComponent::get_item_limit() {
	return item_limit;
}

void InventoryComponent::set_contents(TypedArray<BaseItem> value) {
	contents = value;
}

TypedArray<BaseItem> InventoryComponent::get_contents() {
	return contents;
}