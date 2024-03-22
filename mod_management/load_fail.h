#ifndef LOAD_FAIL_H
#define LOAD_FAIL_H

#include "core/io/resource.h"
#include "core/string/ustring.h"
#include "core/variant/typed_array.h"

#include "mod_init.h"

class LoadFail : Resource {
	GDCLASS(LoadFail, Resource);
private:
	TypedArray<ModInit> fail_list;
public:
	LoadFail();

	void add_load_errors(ModInit *failing);
	void add_many_load_errors(TypedArray<ModInit> failing);

	String get_output();
};

#endif // LOAD_FAIL_H