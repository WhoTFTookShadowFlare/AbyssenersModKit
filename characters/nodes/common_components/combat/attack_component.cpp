#include "attack_component.h"

#include "../../../../projectiles/nodes/projectile.h"
#include "../../../../projectiles/nodes/projectile_manager.h"

AttackComponent::AttackComponent() {}

void AttackComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_attack_rate", "value"), &AttackComponent::set_attack_rate);
	ClassDB::bind_method(D_METHOD("get_attack_rate"), &AttackComponent::get_attack_rate);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "atk_rate"), "set_attack_rate", "get_attack_rate");

	ClassDB::bind_method(D_METHOD("set_atk_dir", "value"), &AttackComponent::set_atk_dir);
	ClassDB::bind_method(D_METHOD("get_atk_dir"), &AttackComponent::get_atk_dir);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "atk_dir"), "set_atk_dir", "get_atk_dir");

	ClassDB::bind_method(D_METHOD("set_atk_dist", "value"), &AttackComponent::set_atk_dist);
	ClassDB::bind_method(D_METHOD("get_atk_dist"), &AttackComponent::get_atk_dist);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "atk_dist"), "set_atk_dist", "get_atk_dist");

	ClassDB::bind_method(D_METHOD("set_equiped_item", "value"), &AttackComponent::set_equiped_item);
	ClassDB::bind_method(D_METHOD("get_equiped_item"), &AttackComponent::get_equiped_item);
	ADD_PROPERTY(PropertyInfo(
		Variant::OBJECT, "equiped_item",
		PROPERTY_HINT_RESOURCE_TYPE, BaseItem::get_class_static()
	), "set_equiped_item", "get_equiped_item");
}

void AttackComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
		case NOTIFICATION_READY: {
			Node *parent = get_parent();
			ERR_FAIL_COND_MSG(!parent->is_class(WorldCharacter::get_class_static()), "Parent of AttackComponent was not a WorldCharacter");
			character = cast_to<WorldCharacter>(parent);

			set_physics_process_internal(true);
		};
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
			if(atk_dir.is_zero_approx()) return;

			Vector3 aim = atk_dir.normalized();
			Ref<BaseItem> use = get_equiped_item();
			if(use.is_null()) use = character->get_character_data()->get_species()->get_default_weapon();
			ERR_FAIL_COND_MSG(use.is_null(), "No useable weapon on an AttackComponent");
			
			Variant proj_var = use->call("get_projectile", character);
			ERR_FAIL_COND_MSG(proj_var.get_type() != Variant::OBJECT, "get_projectile must return a Projectile");
			Object *proj_obj = proj_var.operator Object *();
			ERR_FAIL_COND_MSG(!proj_obj->is_class(Projectile::get_class_static()), "get_projectile must return a Projectile");
			Projectile *proj = cast_to<Projectile>(proj_obj);
			if(!proj->is_inside_tree()) ProjectileManager::get_singleton()->add_child(proj);
		} break;
	}
}

void AttackComponent::set_attack_rate(float value) {
	attack_rate = MIN(0.001, value);
}

float AttackComponent::get_attack_rate() {
	return attack_rate;
}

void AttackComponent::set_atk_dir(Vector3 value) {
	atk_dir = value;
}

Vector3 AttackComponent::get_atk_dir() {
	return atk_dir;
}

void AttackComponent::set_atk_dist(float value) {
	atk_dist = value;
}

float AttackComponent::get_atk_dist() {
	return atk_dist;
}

void AttackComponent::set_equiped_item(Ref<BaseItem> value) {
	equiped_item = value;
}

Ref<BaseItem> AttackComponent::get_equiped_item() {
	return equiped_item;
}
