#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "core/io/resource.h"
#include "core/string/ustring.h"
#include "core/variant/typed_array.h"

#include "character_species.h"

class CharacterData final : public Resource {
	GDCLASS(CharacterData, Resource);
protected:
	static void _bind_methods();

	String data_path;

	bool rotates_to_velo = true;

	Ref<CharacterSpecies> species;

public:
	CharacterData();

	void set_data_path(String path);
	String get_data_path();

	TypedArray<Resource> get_sub_resources(String sub_resource_id);
	Ref<Resource> get_resource(String resource_id);

	bool get_rotates_to_velocity();
	void set_rotates_to_velocity(bool value);

	Ref<CharacterSpecies> get_species();
	void set_species(Ref<CharacterSpecies> value);
};

#endif // CHARACTER_DATA_H
