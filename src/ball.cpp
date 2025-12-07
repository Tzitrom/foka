#include "ball.h" //Azert hogy lassuk a ball.h tartalmat
#include "player.h" //Hogy lassa a Player osztalyt

#include <godot_cpp/core/class_db.hpp> //Kotelezo
#include <godot_cpp/variant/utility_functions.hpp> //print miatt
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/input.hpp>

#include <cmath> //fmod miatt

using namespace godot; //Ha nem akarod odatenni minden sor ele hogy godot:: xd

Ball::Ball() {} //Konstruktor
Ball::~Ball() {} //Destruktor

void Ball::_bind_methods() { //Azert hogy a godot tudja hasznalni a fuggvenyeket
	
}

void Ball::_ready() { //amikor elindul a program
}


void Ball::_process(double delta) {
	Vector2 pos = get_global_position();
	Vector2 dir = (target - pos).normalized();

	// mozgas
	pos += dir * speed * (float)delta;
	set_global_position(pos);

	//meghal amikor eleri az egeret
	if (pos.distance_to(target) < 5.0f) {
		queue_free();
	}
}

