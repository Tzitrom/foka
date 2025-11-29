// Ez a player.h header kifejtese. Itt futnak le a fuggvenyek.

#include "player.h" //Azert hogy lassuk a player.h tartalmat
#include "jumpButton.h" // Azert hogy tudjuk hasznalni a jumpButton-t
#include <godot_cpp/core/class_db.hpp>  //Kotelezo
#include <godot_cpp/classes/input.hpp>

using namespace godot;  //Ha nem akarod odatenni minden sor ele hogy godot:: xd

void Player::_bind_methods() {   //Azert hogy a godot tudja hasznalni a fuggvenyeket
	ClassDB::bind_method(D_METHOD("jump"), &Player::jump);   //A Player::jump() fuggvenyt elerhetove tesszuk a Godot szamara "jump" neven
}

Player::Player() {  //Konstruktor
	gravity = -981;  //Gravitacio (valtoztathato, csak negativ legyen, hogy lefele essen a karakter)
	jump_possible = false;  //tud-e ugrani a karakter
}

Player::~Player() { //Destruktor (felesleges)
}

void Player::_process(double delta) {   //Ez az alap godot fuggveny, ami minden frameben lefut. a delta az eltelt ido az elozo frame ota
	/* --GRAVITACIO HUZASA LEFELE-- */
	set_velocity(get_velocity() - Vector2(0, gravity) * delta);   //Az uj sebesseg = a regi sebesseg - egy vektor ami vizszintesen 0 es fuggolegesen gravity * delta (delta azert kell mert kulonben a sebesseg fuggne a fps-tol)
	/* --UGRAS-- */
	if (is_on_floor() && Input::get_singleton()->is_action_pressed("ugras")) {  //Ha a karakter a foldon van es kapunk egy olyan inputot hogy "ugras" (be van allitva 'W'-re, 'Felfele nyil'-ra es 'Space'-re)
		jump();
	}
	/* --MOZGAS--*/
	float x = Input::get_singleton()->get_axis("balra", "jobbra");
	if (abs(get_velocity().x) <= MAX_SPEED) {
		set_velocity(get_velocity() + Vector2(x, 0) * SPEED);
	}
	if (get_velocity().x >= MAX_SPEED) {set_velocity(Vector2(MAX_SPEED, get_velocity().y));}
	if (get_velocity().x <= -MAX_SPEED) { set_velocity(Vector2(-MAX_SPEED, get_velocity().y));}
	move_and_slide(); //Mozgatja a karaktert, az utkozeskor lenullazza a sebesseget az adott iranyban

	/* --TESZTKIIRAS-- */
	UtilityFunctions::print(get_velocity()); //Kiir a konzolra valamit, nyugodtan allitsuk hogy eppen mit, tesztelesi okokbol
}

void Player::_ready() {  //Ez alap godot fuggveny, ami akkor fut le, amikor a karakterunk bejon a kepbe, magyarul amikor elindul a program
	(Error)get_node<Button>("jumpButton")->connect("gomb_pressed", Callable(this, "jump"));  //A jumpButton gomb altal kivaltott "gomb_pressed" jelet osszekapcsolja a Player osztaly "jump" fuggvenyevel
	count++;  //felesleges 
}


void Player::jump() {//ugras fuggveny
		set_velocity(get_velocity() + Vector2(0, JUMP_SIZE));  //A sebesseghez hozzaad egy vektort, ami vizszintesen 0 es fuggolegesen JUMP_SIZE (negativ mert felfele akarunk ugrani)
		count++; //ugras szamlalo (felesleges)
}

void Player::move() {
}
