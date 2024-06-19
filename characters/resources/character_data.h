#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "core/io/resource.h"
#include "core/string/ustring.h"
#include "core/variant/typed_array.h"
#include "core/variant/dictionary.h"

#include "character_species.h"
#include "character_layer_info.h"

class CharacterData final : public Resource {
	GDCLASS(CharacterData, Resource);
protected:
	static void _bind_methods();

	bool rotates_to_velo = true;

	TypedArray<Dictionary> required_components;

	Ref<CharacterSpecies> species;

	TypedArray<CharacterLayerInfo> parts;
	TypedArray<CharacterLayerInfo> patterns;

	double height = 1.0;
	double width = 0.2;
public:
	CharacterData();

	void set_required_components(TypedArray<Dictionary> value);
	TypedArray<Dictionary> get_required_components();

	bool get_rotates_to_velocity();
	void set_rotates_to_velocity(bool value);

	Ref<CharacterSpecies> get_species();
	void set_species(Ref<CharacterSpecies> value);

	TypedArray<CharacterLayerInfo> get_parts();
	void set_parts(TypedArray<CharacterLayerInfo> value);

	TypedArray<CharacterLayerInfo> get_patterns();
	void set_patterns(TypedArray<CharacterLayerInfo> value);

	double get_height();
	void set_height(double value);

	double get_width();
	void set_width(double value);
};

#endif // CHARACTER_DATA_H
