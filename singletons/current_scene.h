#ifndef CURRENT_SCENE_H
#define CURRENT_SCENE_H

#include "scene/main/node.h"

class CurrentScene final : public Node {
	GDCLASS(CurrentScene, Node);
protected:
	static CurrentScene *singleton;

	String scene_id;

	static void _bind_methods();

public:
	static CurrentScene *get_singleton();
	CurrentScene();

	void _setup();

	void set_scene(String id);
	String get_scene();
};

#endif // CURRENT_SCENE_H