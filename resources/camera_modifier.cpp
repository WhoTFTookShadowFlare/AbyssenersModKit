#include "camera_modifier.h"

void CameraModifier::_bind_methods() {
	{
		PackedStringArray arg_names;
		arg_names.append("camera");
		ClassDB::add_virtual_method(CameraModifier::get_class_static(), MethodInfo(Variant::NIL, "update_camera", PropertyInfo("GameCamera")), true, arg_names);
	}
}

CameraModifier::CameraModifier() {}