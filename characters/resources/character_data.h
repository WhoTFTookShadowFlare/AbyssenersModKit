#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "core/io/resource.h"
#include "core/string/ustring.h"
#include "core/variant/typed_array.h"

#include "character_species.h"
#include "character_pattern_info.h"

class CharacterData final : public Resource {
	GDCLASS(CharacterData, Resource);
protected:
	static void _bind_methods();

	bool rotates_to_velo = true;

	TypedArray<String> required_components;

	Ref<CharacterSpecies> species;

	Color pri_color;

	Color l_eye_color;
	Color r_eye_color;

	TypedArray<CharacterPatternInfo> patterns;
public:
	CharacterData();

	void set_required_components(TypedArray<String> value);
	TypedArray<String> get_required_components();

	bool get_rotates_to_velocity();
	void set_rotates_to_velocity(bool value);

	Ref<CharacterSpecies> get_species();
	void set_species(Ref<CharacterSpecies> value);

	Color get_primary_color();
	void set_primary_color(Color value);

	Color get_left_eye_color();
	void set_left_eye_color(Color value);

	Color get_right_eye_color();
	void set_right_eye_color(Color value);

	TypedArray<CharacterPatternInfo> get_patterns();
	void set_patterns(TypedArray<CharacterPatternInfo> value);
};

#endif // CHARACTER_DATA_H
