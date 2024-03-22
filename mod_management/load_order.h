#ifndef LOAD_ORDER_H
#define LOAD_ORDER_H

#include "core/io/resource.h"
#include "core/variant/typed_array.h"
#include "core/string/ustring.h"

class LoadOrder final : public Resource {
	GDCLASS(LoadOrder, Resource);
private:
	TypedArray<String> order_list;

protected:
	static void _bind_methods();

public:
	LoadOrder();

	void swap(int a, int b);
	void add(String file);
	void remove(String file);

	TypedArray<String> get_list();
	void set_list(TypedArray<String> list);
};

#endif // LOAD_ORDER_H