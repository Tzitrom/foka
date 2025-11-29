#include "jumpButton.h"//Azert hogy lassuk a jumpButton.h tartalmat
#include "player.h"// Azert hogy tudjuk hasznalni a Player-t
#include <godot_cpp/core/class_db.hpp>//Kotelezo

using namespace godot;//Ha nem akarod odatenni minden sor ele hogy godot:: xd

void jumpButton::_bind_methods() { //Azert hogy a godot tudja hasznalni a fuggvenyeket
	ADD_SIGNAL(MethodInfo("gomb_pressed")); //Letrehoz egy "gomb_pressed" jelet, ami gyakorlatilag olyan mintha a jumpButton elorditana magat, hogy a gombot megnyomtak
	ADD_SIGNAL(MethodInfo("print")); //Letrehoz egy "print" jelet (felesleges)
}


void jumpButton::jumpEmit() { //felesleges
	if (&BaseButton::is_pressed) {
		Button::emit_signal("gomb_pressed");
	}
}

void jumpButton::testprint() { //ures :(
}

void jumpButton::print() {  //tesztkiiras
	UtilityFunctions::print("hello");
}

void jumpButton::_process(double delta) {  //Minden frameben meghivodik
	if (BaseButton::is_pressed()) {  //Ha a gomb le van nyomva
		if (!is_pressed) { //Ha eddig nem volt lenyomva
			Button::emit_signal("gomb_pressed"); //Kuld egy jelet, hogy a gombot megnyomtak
			is_pressed = true; //Beallitja, hogy a gomb le van nyomva
		}
	}
	else { //Ha a gomb nincs lenyomva
		is_pressed = false; //Beallitja, hogy a gomb nincs lenyomva
	}
}

