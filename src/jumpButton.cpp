#include "jumpButton.h"//Azért hogy lássuk a jumpButton.h tartalmát
#include "player.h"// Azért hogy tudjuk használni a Player-t
#include <godot_cpp/core/class_db.hpp>//Kötelezõ

using namespace godot;//Ha nem akarod odatenni minden sor elé hogy godot:: xd

void jumpButton::_bind_methods() { //Azért hogy a godot tudja használni a függvényeket
	ADD_SIGNAL(MethodInfo("gomb_pressed")); //Létrehoz egy "gomb_pressed" jelet, ami gyakorlatilag olyan mintha a jumpButton mindenkinek írna egy üzenetet, hogy a gombot megnyomták
	ADD_SIGNAL(MethodInfo("print")); //Létrehoz egy "print" jelet (felesleges)
}


void jumpButton::jumpEmit() { //felesleges
	if (&BaseButton::is_pressed) {
		Button::emit_signal("gomb_pressed");
	}
}

void jumpButton::testprint() { //üres :(
}

void jumpButton::print() {  //tesztkiírás
	UtilityFunctions::print("hello");
}

void jumpButton::_process(double delta) {  //Minden frameben meghívódik
	if (BaseButton::is_pressed()) {  //Ha a gomb le van nyomva
		if (!is_pressed) { //Ha eddig nem volt lenyomva
			Button::emit_signal("gomb_pressed"); //Küld egy jelet, hogy a gombot megnyomták
			is_pressed = true; //Beállítja, hogy a gomb le van nyomva
		}
	}
	else { //Ha a gomb nincs lenyomva
		is_pressed = false; //Beállítja, hogy a gomb nincs lenyomva
	}
}

