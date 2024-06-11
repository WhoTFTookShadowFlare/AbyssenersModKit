#ifndef CHARACTER_PATTERN_INFO_H
#define CHARACTER_PATTERN_INFO_H

#include "core/io/resource.h"

class CharacterLayerInfo : public Resource {
	GDCLASS(CharacterLayerInfo, Resource);
protected:
	static void _bind_methods();

	Color layer_color;
	String layer_id;
public:
	CharacterLayerInfo();

	Color get_layer_color();
	void set_layer_color(Color value);

	String get_layer_id();
	void set_layer_id(String id);
};

#endif // CHARACTER_PATTERN_INFO_H