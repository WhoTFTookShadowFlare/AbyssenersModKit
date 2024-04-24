#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "scene/3d/camera_3d.h"

#include "../resources/camera_modifier.h"
#include "../resources/save_file.h"

class GameCamera final : public Camera3D {
	GDCLASS(GameCamera, Camera3D);
protected:
	static GameCamera *singleton;

	static void _bind_methods();
	void _setup();
	void _notification(int p_what);

	void _save(Ref<SaveFile> file);
	void _load(Ref<SaveFile> file);

	TypedArray<CameraModifier> modifiers;
public:
	static GameCamera *get_singleton();
	GameCamera();

	TypedArray<CameraModifier> get_modifiers();
	void set_modifiers(TypedArray<CameraModifier> mods);

	void add_modifier(Ref<CameraModifier> modifier);
	void remove_modifier(Ref<CameraModifier> modifier);
};

#endif // GAME_CAMERA_H