#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "core/io/resource.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"
#include "core/string/ustring.h"

class SaveFile final : public Resource {
	GDCLASS(SaveFile, Resource);
protected:
	Dictionary data;
	static void _bind_methods();

	void set_data_value(Dictionary data_val);
	Dictionary get_data_value();
public:
	SaveFile();

	void set_data(String id, Variant value);
	bool has_data(String id);
	Variant get_data(String id);

	Variant get_or_default(String id, Variant default_val);
};

#endif // SAVE_FILE_H