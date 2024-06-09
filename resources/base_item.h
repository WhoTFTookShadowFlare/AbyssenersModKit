#ifndef BASE_ITEM_H
#define BASE_ITEM_H

#include "core/io/resource.h"

class BaseItem : public Resource {
	GDCLASS(BaseItem, Resource);
protected:
	static void _bind_methods();
	
	int count = 1;
	int max_count = 1000000;

	String cosmetic_sprites_dir;

public:
	BaseItem();

	bool should_be_removed();
	bool can_merge_with(Ref<BaseItem> other);

	bool is_max_count();

	void set_count(int value);
	int get_count() const;

	void set_max_count(int value);
	int get_max_count();

	void set_cosmetic_sprites_dir(String location);
	String get_cosmetic_sprites_dir();
};

#endif // BASE_ITEM_H