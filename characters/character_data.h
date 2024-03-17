#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "core/io/resource.h"
#include "core/string/ustring.h"

class CharacterData final : public Resource {
	GDCLASS(CharacterData, Resource);

protected:
	static void _bind_methods();

	String data_path;

public:
	CharacterData();

	void set_data_path(String path);
	String get_data_path();
};

#endif // CHARACTER_DATA_H
