#ifndef INVENTORY_COMPONENT_H
#define INVENTORY_COMPONENT_H

#include "scene/main/node.h"

#include "core/variant/typed_array.h"
#include "core/io/resource.h"
#include "core/object/script_language.h"

#include "../../resources/base_item.h"

class InventoryComponent : public Node {
	GDCLASS(InventoryComponent, Node);
protected:
	static void _bind_methods();

	TypedArray<BaseItem> contents;

	int item_limit;

public:
	InventoryComponent();

	bool can_add(Ref<BaseItem> item);
	void add_item(Ref<BaseItem> item);

	bool has_item(Ref<Script> item_type);
	Ref<BaseItem> get_item(Ref<Script> item_type);
	void remove_item(Ref<Script> item_type);

	bool filter_fn(Variant entry);
	void clean_empty();
	
	void set_item_limit(int value);
	int get_item_limit();

	void set_contents(TypedArray<BaseItem> value);
	TypedArray<BaseItem> get_contents();
};

#endif // INVENTORY_COMPONENT_H