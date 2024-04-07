#include "movement_component.h"

#include "scene/resources/world_2d.h"

MovementComponent::MovementComponent() {}

void MovementComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &MovementComponent::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "value"), &MovementComponent::set_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void MovementComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_READY: {
		set_physics_process_internal(true);

		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		character = cast_to<WorldCharacter>(parent);
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		if(!character) return;

		Vector2 mv_dir = get_next_path_position() - character->get_position();
		character->set_velocity(character->get_velocity() + mv_dir * (speed * 32.0));
	} break;
	default:
		break;
	}
}

double MovementComponent::get_speed() {
	return speed;
}

void MovementComponent::set_speed(double value) {
	speed = value;
}
