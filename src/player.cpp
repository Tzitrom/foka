#include "player.h"
#include "jumpButton.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("jump"), &Player::jump);
}

Player::Player() {
	gravity = 0;
	jump_signal = false;
}

Player::~Player() {
}

void Player::_process(double delta) {
	set_velocity(get_velocity() - Vector2(0, gravity) * delta);
	move_and_collide(get_velocity());
	gravity = gravity - 0.2;
}

void Player::_ready() {
	get_node<Button>("jumpButton")->connect("gomb_pressed", Callable(this, "jump"));
}


void Player::jump() {
	UtilityFunctions::print("Player::jump() called");
	set_position(get_position() + Vector2(0, -40));
	set_velocity(Vector2(0, -300));
}
