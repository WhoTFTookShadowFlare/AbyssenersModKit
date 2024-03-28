#ifndef CURRENT_SCENE_H
#define CURRENT_SCENE_H

#include "scene/main/node.h"

#include "../resources/save_file.h"

class CurrentScene final : public Node {
	GDCLASS(CurrentScene, Node);
protected:
	static CurrentScene *singleton;

	String scene_id;

	static void _bind_methods();
	void _setup();
public:
	static CurrentScene *get_singleton();
	CurrentScene();

	void save_scene_id(SaveFile *file);
	void load_scene_id(SaveFile *file);

	void set_scene(String id);
	String get_scene();
};

#endif // CURRENT_SCENE_H