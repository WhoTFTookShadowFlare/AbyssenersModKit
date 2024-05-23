#ifndef ITEM_SIGNALS_H
#define ITEM_SIGNALS_H

#include "core/object/object.h"
#include "core/object/class_db.h"

#include "../resources/base_item.h"
#include "../characters/world_character.h"

class ItemSignals : public Object {
	GDCLASS(ItemSignals, Object);
protected:
	static ItemSignals *singleton;

	static void _bind_methods();

public:
	static ItemSignals *get_singleton();
	ItemSignals();


	void add_item_signal(StringName name);
	void emit_item_signal(StringName name, Ref<BaseItem> item, WorldCharacter *character);
};

#endif // ITEM_SIGNALS_H