#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "scene/3d/sprite_3d.h"

class SpriteComponent : public Sprite3D {
	GDCLASS(SpriteComponent, Sprite3D);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	String current_animation;
	int current_frame = 0;
	float frame_time_rem = 0.0;

	String animations_location;
	Ref<SpriteFrames> animation_data = Ref<SpriteFrames>(memnew(SpriteFrames));

	int direction_count = 4;
	double ANGLE_BETWEEN = 360.0 / (double) direction_count;
	double ANGLE_START_OFF = ANGLE_BETWEEN / 2.0;

public:
	const String ANIMATION_ERROR = "error";
	SpriteComponent();

	void update_texture();

	void set_current_animation(String value);
	String get_current_animation();

	void set_current_frame(int value);
	int  get_current_frame();

	void set_frame_time_remaining(float value);
	float get_frame_time_remaining();

	void set_animations_location(String value);
	String get_animations_location();

	void set_direction_count(int value);
	int get_direction_count();
};

#endif // SPRITE_COMPONENT_H