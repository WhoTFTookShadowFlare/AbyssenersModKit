#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "scene/3d/sprite_3d.h"
#include "scene/2d/node_2d.h"

#include "scene/main/viewport.h"

#include "../../../../resources/base_item.h"
#include "../../../resources/character_data.h"

class SpriteComponent : public Sprite3D {
	GDCLASS(SpriteComponent, Sprite3D);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	SubViewport *render;
	Ref<ViewportTexture> render_texture;

	TypedArray<BaseItem> equiped_items;

	Node2D *char_parts;
	Node2D *char_equip;

	Ref<CharacterData> data;
public:
	SpriteComponent();

	void add_item(Ref<BaseItem> item);
	void remove_item(Ref<BaseItem> item);
	void update_equipment();

};

#endif // SPRITE_COMPONENT_H 