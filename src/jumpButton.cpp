#include "jumpButton.h"
#include "player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void jumpButton::_bind_methods() {
	ADD_SIGNAL(MethodInfo("jump"));
	ADD_SIGNAL(MethodInfo("print"));
}


void jumpButton::jumpEmit() {
	if (&BaseButton::is_pressed) {
		Button::emit_signal("jump", this, &Player::jump);
	}
}

void jumpButton::testprint() {
	Button::emit_signal("print", Callable(this, "print"));
}

void jumpButton::print() {
	UtilityFunctions::print("hello");
}


