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

	TypedArray<BaseItem> equipped_items;

	Node2D *char_layers;
	Node2D *char_equip;

	Ref<CharacterData> data;

	void add_layers_from_array(TypedArray<CharacterLayerInfo> layers, Ref<CharacterSpecies> species);
public:
	SpriteComponent();

	void set_equipped_items(TypedArray<BaseItem> items);
	TypedArray<BaseItem> get_equipped_items();
	void update_equipment();

	void update_layers();
};

#endif // SPRITE_COMPONENT_H 