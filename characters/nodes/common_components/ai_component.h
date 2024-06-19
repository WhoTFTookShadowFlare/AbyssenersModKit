#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "scene/main/node.h"

#include "../world_character.h"
#include "../../resources/ai/ai_tree.h"

class AIComponent : public Node {
	GDCLASS(AIComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	String ai_tree_path;

	Ref<AITree> ai_tree;
	WorldCharacter *character = nullptr;
public:
	AIComponent();

	void set_ai_tree(Ref<AITree> value);
	Ref<AITree> get_ai_tree();

	void set_ai_tree_path(String value);
	String get_ai_tree_path();
};

#endif // AI_COMPONENT_H