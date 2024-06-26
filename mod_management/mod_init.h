#ifndef MOD_INIT_H
#define MOD_INIT_H

#include "scene/main/node.h"
#include "core/variant/typed_array.h"

class ModInit : public Node {
	GDCLASS(ModInit, Node);
private:
	static void _bind_methods();

	bool has_loaded = false;
public:
	ModInit();

	void set_loaded();
	bool is_loaded();
};

#endif // MOD_INIT_H