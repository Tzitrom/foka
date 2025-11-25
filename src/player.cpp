#include "player.h"
#include "jumpButton.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("jump"), &Player::jump);
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

	if (jump_signal) {
		jump();
	}
}

void Player::_ready() {
	(Error)get_node<Button>("jumpButton")->connect("gomb_pressed", Callable(this, "jump"));
	count++;
}


void Player::jump() {
	set_velocity(Vector2(0, -2));
	count++;
}
