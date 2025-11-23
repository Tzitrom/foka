#include "player.h"
#include "jumpButton.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods() {
}

Player::Player() {
	gravity = -9.81;
	jump_signal = false;
}

Player::~Player() {
}

void Player::_process(double delta) {
	set_velocity(get_velocity() - Vector2(0, gravity) * delta);
	move_and_collide(get_velocity());
}

void Player::jump() {
	if (CharacterBody2D::has_signal("jump")) {
		UtilityFunctions::print("I am typing from C++");
	}
}