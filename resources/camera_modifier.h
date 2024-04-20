#ifndef CAMERA_MODIFIER_H
#define CAMERA_MODIFIER_H

#include "core/io/resource.h"

class CameraModifier : public Resource {
	GDCLASS(CameraModifier, Resource);
protected:
	static void _bind_methods();
public:
	CameraModifier();
};

#endif // CAMERA_MODIFIER_H