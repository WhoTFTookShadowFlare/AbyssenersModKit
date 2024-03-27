#ifndef MOD_LOADER_H
#define MOD_LOADER_H

#include "scene/main/node.h"

#include "mod_init.h"
#include "load_order.h"

class ModLoader : public Node {
	GDCLASS(ModLoader, Node);
private:

protected:
	static ModLoader* singleton;
	static void _bind_methods();

	LoadOrder load_order;
	bool already_loaded = false;

public:
	ModLoader();
	static ModLoader* get_singleton();

	void load_content();

	bool has_mod(String mod_id);
	bool is_mod_loaded(String mod_id);
	ModInit *get_mod_init(String mod_id);
};

#endif // MOD_LOADER_H