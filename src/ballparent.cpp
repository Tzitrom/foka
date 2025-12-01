#include "ballparent.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

BallParent::BallParent() {
}

BallParent::~BallParent() {
}

void BallParent::_bind_methods() {
}

void BallParent::_ready() {
}

void BallParent::_process(double delta) {
	set_global_position(get_global_mouse_position());
}