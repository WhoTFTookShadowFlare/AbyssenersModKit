#ifndef CHARACTER_PATTERN_INFO_H
#define CHARACTER_PATTERN_INFO_H

#include "core/io/resource.h"

class CharacterPatternInfo : public Resource {
	GDCLASS(CharacterPatternInfo, Resource);
protected:
	static void _bind_methods();

	Color pattern_color;
	String pattern_id;
public:
	CharacterPatternInfo();

	Color get_pattern_color();
	void set_pattern_color(Color value);

	String get_pattern_id();
	void set_pattern_id(String id);
};

#endif // CHARACTER_PATTERN_INFO_H