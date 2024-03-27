#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include "scene/main/node.h"
#include "core/variant/typed_array.h"
#include "core/string/ustring.h"

#include "../resources/save_file.h"

class SaveManager final : public Object {
	GDCLASS(SaveManager, Object);
protected:
	static SaveManager *singleton;
	static void _bind_methods();

	String game_file_name;
	Ref<SaveFile> game_file;
	Ref<SaveFile> global_file;

public:
	SaveManager();
	~SaveManager();
	static SaveManager *get_singleton();
	String get_global_file_path() const;

	PackedStringArray get_save_files();

	void write_save_files();

	Ref<SaveFile> get_game_file();
	Ref<SaveFile> get_global_file();

	void set_game_file_name(String name);
	String get_game_file_name();
};

#endif // SAVE_MANAGER_H