#include "pathing_component.h"

#include "scene/resources/world_2d.h"

PathingComponent::PathingComponent() {}

void PathingComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &PathingComponent::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "value"), &PathingComponent::set_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void PathingComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_PARENTED: {
		set_physics_process_internal(true);

		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		character = cast_to<WorldCharacter>(parent);
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		if(!character) return;

		Vector3 mv_dir = get_next_path_position() - character->get_position();
		if(mv_dir.y < 0.0) mv_dir.y = 0.0;
		character->set_velocity(character->get_velocity() + (mv_dir * speed));
	} break;
	default:
		break;
	}
}

double PathingComponent::get_speed() {
	return speed;
}

void PathingComponent::set_speed(double value) {
	speed = value;
}
