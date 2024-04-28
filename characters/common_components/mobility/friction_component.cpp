#include "friction_component.h"

void FrictionComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_friction"), &FrictionComponent::get_friction);
	ClassDB::bind_method(D_METHOD("set_friction", "value"), &FrictionComponent::set_friction);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "friction"), "set_friction", "get_friction");

	ClassDB::bind_method(D_METHOD("get_air_resistance"), &FrictionComponent::get_air_resistance);
	ClassDB::bind_method(D_METHOD("set_air_resistance"), &FrictionComponent::set_air_resistance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "air_resistance"), "set_air_resistance", "get_air_resistance");
}

FrictionComponent::FrictionComponent() {}

void FrictionComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
		case NOTIFICATION_READY: {
			Node *parent = get_parent();
			ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
			character = cast_to<WorldCharacter>(parent);
			set_physics_process_internal(true);
		}; break;
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
			if(!character) {
				ERR_PRINT_ONCE("Cannot apply to friction to nobody");
				return;
			}

			Vector3 velo = character->get_velocity();
			velo.x /= (character->is_on_floor() ? friction : air_resistance);
			velo.z /= (character->is_on_floor() ? friction : air_resistance);
			character->set_velocity(velo);
		}; break;
	}
}

double FrictionComponent::get_friction() {
	return friction;
}

void FrictionComponent::set_friction(double value) {
	friction = value;
}

double FrictionComponent::get_air_resistance() {
	return air_resistance;
}

void FrictionComponent::set_air_resistance(double value) {
	air_resistance = value;
}