#include "../projectile.h"

#include "../../../characters/nodes/world_character.h"

class FollowCharacterComponent : public Node {
	GDCLASS(FollowCharacterComponent, Node);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	NodePath target;
	WorldCharacter *target_char;
	Vector3 offset;

	Projectile *projectile;

public:
	FollowCharacterComponent();

	void set_target_character_path(NodePath value);
	NodePath get_target_character_path();

	void set_target_character(WorldCharacter *value);
	WorldCharacter *get_target_character();

	void set_offset(Vector3 value);
	Vector3 get_offset();
};