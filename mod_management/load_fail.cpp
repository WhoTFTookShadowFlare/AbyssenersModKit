#include "load_fail.h"

LoadFail::LoadFail() {}

void LoadFail::add_load_errors(ModInit *init) {
	fail_list.append(init);
}

void LoadFail::add_many_load_errors(TypedArray<ModInit> failing) {
	fail_list.append_array(failing);
}

String LoadFail::get_output() {
	String output = "Failed to load " + Variant(fail_list.size()).stringify() + " mods:\n";

	for(int idx = 0; idx < fail_list.size(); idx++) {
		ModInit *init = cast_to<ModInit>(fail_list[idx]);
		PackedStringArray errors = init->call("get_load_errors");

		output += init->get_name();
		output += " (" + Variant(errors.size()).stringify() + "):\n";
		for(String err : errors) 
			output += "\t" + err + "\n";
	}

	return output;
}