#ifndef CURRENT_SCENE_H
#define CURRENT_SCENE_H

#include "scene/main/node.h"
#include "core/variant/typed_array.h"
#include "core/variant/callable.h"

#include "../resources/save_file.h"

class CurrentScene final : public Node {
	GDCLASS(CurrentScene, Node);
protected:
	static CurrentScene *singleton;

	String scene_id;

	TypedArray<Callable> resource_handler_array = TypedArray<Callable>();

	static void _bind_methods();
	void _setup();
	void _notification(int p_what);

	bool _handle_packed_scene(Ref<Resource> resource);
	bool _handle_environment(Ref<Resource> resource);
public:
	static CurrentScene *get_singleton();
	CurrentScene();

	void save_scene_id(SaveFile *file);
	void load_scene_id(SaveFile *file);

	void set_scene(String id);
	String get_scene();

	void add_resource_handler(Callable handler);
};

#endif // CURRENT_SCENE_H