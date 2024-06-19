#ifndef BASE_CONDITION_H
#define BASE_CONDITION_H

#include "core/io/resource.h"

class BaseCondition : public Resource {
	GDCLASS(BaseCondition, Resource);
protected:
	static void _bind_methods();
public:
	BaseCondition();
};

#endif // BASE_CONDITION_H