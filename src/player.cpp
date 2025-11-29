// Ez a player.h header kifejtése. Itt futnak le a függvények.

#include "player.h" //Azért hogy lássuk a player.h tartalmát
#include "jumpButton.h" // Azért hogy tudjuk használni a jumpButton-t
#include <godot_cpp/core/class_db.hpp>  //Kötelezõ

using namespace godot;  //Ha nem akarod odatenni minden sor elé hogy godot:: xd

void Player::_bind_methods() {   //Azért hogy a godot tudja használni a függvényeket
	ClassDB::bind_method(D_METHOD("jump"), &Player::jump);   //A Player::jump() függvényt elérhetõvé tesszük a Godot számára "jump" néven
}

Player::Player() {  //Konstruktor
	gravity = -981;  //Gravitáció (változtatható, csak negatív legyen, hogy lefele essen a karakter)
	jump_possible = false;  //tud-e ugrani a karakter
}

Player::~Player() { //Destruktor (felesleges)
}

void Player::_process(double delta) {   //Ez az alap godot függvény, ami minden frameben lefut. a delta az eltelt idõ az elõzõ frame óta
	set_velocity(get_velocity() - Vector2(0, gravity) * delta);   //Az új sebesség = a régi sebesség - egy vektor ami vízszintesen 0 és függõlegesen gravity * delta (delta azért kell mert különben a sebesség függne a fps-tõl)
 	move_and_slide(); //Mozgatja a karaktert, az ütközéskor lenullázza a sebességet az adott irányban

	UtilityFunctions::print(CharacterBody2D::get_slide_collision_count()); //Kiírja a konzolra, hogy hány objektummal ütközik a karakter minden frameben
	if (is_on_floor()) {  //Ha a karakter a földön van
		jump_possible = true;  //akkor lehet ugrani
	} else {
		jump_possible = false; //egyébként nem lehet ugrani
	}
}

void Player::_ready() {  //Ez alap godot függvény, ami akkor fut le, amikor a karakterünk bejön a képbe, magyarul amikor elindul a program
	(Error)get_node<Button>("jumpButton")->connect("gomb_pressed", Callable(this, "jump"));  //A jumpButton gomb általt kiváltott "gomb_pressed" jelet összekapcsolja a Player osztály "jump" függvényével
	count++;  //felesleges 
}


void Player::jump() {//ugrás függvény
	if (jump_possible) { //ha lehet ugrani
		set_velocity(Vector2(0, -200));  //A sebességhez hozzáad egy vektort, ami vízszintesen 0 és függõlegesen -2 (negatív mert felfele akarunk ugrani)
		count++; //ugrás számláló (felesleges)
	}
}
