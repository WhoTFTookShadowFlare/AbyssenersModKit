#include "projectile_manager.h"

#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

ProjectileManager *ProjectileManager::singleton;

ProjectileManager *ProjectileManager::get_singleton() {
	return singleton;
}

ProjectileManager::ProjectileManager() {
	singleton = this;
}

void ProjectileManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_setup"), &ProjectileManager::_setup);

	ClassDB::bind_method(D_METHOD("spawn_projectile"), &ProjectileManager::spawn_projectile);
	ClassDB::bind_method(D_METHOD("spawn_projectile_for", "who"), &ProjectileManager::spawn_projectile_for);
}

void ProjectileManager::_setup() {
	SceneTree::get_singleton()->get_root()->add_child(this);
}

Projectile *ProjectileManager::spawn_projectile() {
	Projectile *proj = memnew(Projectile);
	proj->set_damage_source(Ref<DamageSource>(memnew(DamageSource)));
	add_child(proj);
	return proj;
}

Projectile *ProjectileManager::spawn_projectile_for(WorldCharacter *character) {
	Projectile *proj = spawn_projectile();
	proj->get_damage_source()->set_causing_char(character);
	return proj;
}