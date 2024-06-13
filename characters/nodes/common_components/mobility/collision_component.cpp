#include "collision_component.h"

#include "../../world_character.h"

#include "scene/resources/3d/capsule_shape_3d.h"

CollisionComponent::CollisionComponent() {}

void CollisionComponent::_bind_methods() {

}

void CollisionComponent::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			Node *parent = get_parent();
			ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
			WorldCharacter *character = cast_to<WorldCharacter>(parent);

			Ref<CapsuleShape3D> collider = Ref<Shape3D>(memnew(CapsuleShape3D));
			set_shape(collider);

			collider->set_radius(character->get_character_data()->get_width());
			collider->set_height(character->get_character_data()->get_height());
		};
	}
}