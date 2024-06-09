#include "gravity_component.h"

void GravityComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_gravity", "value"), &GravityComponent::set_gravity);
	ClassDB::bind_method(D_METHOD("get_gravity"), &GravityComponent::get_gravity);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity"), "set_gravity", "get_gravity");
}

GravityComponent::GravityComponent() {}

void GravityComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
		case NOTIFICATION_PARENTED: {
			Node *parent = get_parent();
			ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
			character = cast_to<WorldCharacter>(parent);

			set_physics_process_internal(true);
		}; break;
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
			if(!character) return;

			Vector3 velo = character->get_velocity();
			velo.y -= gravity * get_physics_process_delta_time();
			character->set_velocity(velo);
		}; break;
	}
}

double GravityComponent::get_gravity() {
	return gravity;
}

void GravityComponent::set_gravity(double value) {
	gravity = value;
}