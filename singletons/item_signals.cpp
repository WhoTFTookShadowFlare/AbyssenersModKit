#include "item_signals.h"

ItemSignals *ItemSignals::singleton;

ItemSignals::ItemSignals() {
	singleton = this;
}

ItemSignals *ItemSignals::get_singleton() {
	return singleton;
}

void ItemSignals::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_item_signal", "name"), &ItemSignals::add_item_signal);
	ClassDB::bind_method(D_METHOD("emit_item_signal", "name", "item", "character"), &ItemSignals::emit_item_signal);
}

void ItemSignals::add_item_signal(StringName name) {
	add_user_signal(MethodInfo(Variant::NIL, name, PropertyInfo(Variant::OBJECT, "item"), PropertyInfo(Variant::OBJECT, "character")));
}

void ItemSignals::emit_item_signal(StringName name, Ref<BaseItem> item, WorldCharacter *character) {
	ERR_FAIL_COND(!has_signal(name));
	ERR_FAIL_COND(item.is_null());
	ERR_FAIL_COND_MSG(!character, "Got no character for the item used.");
	List<Object::Connection> connections;
	get_signal_connection_list(name, &connections);
	for(Object::Connection connection : connections) {
		connection.callable.call(item, character);
	}
}