#include "dodge_component.h"

#include "../../world_character.h"

DodgeComponent::DodgeComponent() {}

void DodgeComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("handle_damage", "source"), &DodgeComponent::handle_damage);

	ClassDB::bind_method(D_METHOD("set_dodge_chance", "value"), &DodgeComponent::set_dodge_chance);
	ClassDB::bind_method(D_METHOD("get_dodge_chance"), &DodgeComponent::get_dodge_chance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dodge_chance"), "set_dodge_chance", "get_dodge_chance");

	ClassDB::bind_method(D_METHOD("set_dodge_penalty", "value"), &DodgeComponent::set_dodge_penalty);
	ClassDB::bind_method(D_METHOD("get_dodge_penalty"), &DodgeComponent::get_dodge_penalty);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dodge_penalty"), "set_dodge_penalty", "get_dodge_penalty");

	ClassDB::bind_method(D_METHOD("set_dodge_penalty_rem", "value"), &DodgeComponent::set_dodge_penalty_rem);
	ClassDB::bind_method(D_METHOD("get_dodge_penalty_rem"), &DodgeComponent::get_dodge_penalty_rem);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dodge_penalty_rem"), "set_dodge_penalty_rem", "get_dodge_penalty_rem");
}

void DodgeComponent::_notification(int p_what) {
	if(Engine::get_singleton()->is_editor_hint()) return;

	switch(p_what) {
	case NOTIFICATION_READY: {
		set_physics_process_internal(true);
		Node *parent = get_parent();
		ERR_FAIL_COND(!parent->is_class(WorldCharacter::get_class_static()));
		WorldCharacter *character = cast_to<WorldCharacter>(parent);

		TypedArray<Callable> damage_handlers = character->get_damage_handler_queue();
		damage_handlers.push_front(Callable(this, "handle_damage"));

		for(int c_idx = 0; c_idx < character->get_child_count(); c_idx++) {
			Node *child = character->get_child(c_idx);
			if(child->is_class(LuckComponent::get_class_static())) {
				luck = cast_to<LuckComponent>(child);
				break;
			}
		}
	} break;
	case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		dodge_penalty_rem -= get_physics_process_delta_time();
	} break;
	default:
		break;
	}
}

void DodgeComponent::handle_damage(Ref<DamageSource> source) {
	if(source.is_null()) return;
	if(source->has_flag(DodgeComponent::NO_DODGE_FLAG)) return;

	bool should_dodge;
	if(luck) should_dodge = dodge_chance >= luck->get_rand_float(0.01);
	else {
		Ref<RandomNumberGenerator> rng = Ref<RandomNumberGenerator>(memnew(RandomNumberGenerator));
		should_dodge = dodge_chance >= rng->randf_range(0.0, 1.0);
	}

	if(should_dodge) {
		source->set_amount(0);
	}
}

void DodgeComponent::set_dodge_chance(double value) {
	dodge_chance = CLAMP(value, 0.0, 1.0);
}

double DodgeComponent::get_dodge_chance() {
	return dodge_chance;
}

void DodgeComponent::set_dodge_penalty(double value) {
	dodge_penalty = value;
}

double DodgeComponent::get_dodge_penalty() {
	return dodge_penalty;
}

void DodgeComponent::set_dodge_penalty_rem(double value) {
	dodge_penalty_rem = value;
}

double DodgeComponent::get_dodge_penalty_rem() {
	return dodge_penalty_rem;
}
