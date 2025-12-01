#include "ball.h" //Azert hogy lassuk a ball.h tartalmat
#include "ballparent.h" //Hogy lassa a BallParent osztalyt
#include "player.h" //Hogy lassa a Player osztalyt

#include <godot_cpp/core/class_db.hpp> //Kotelezo
#include <godot_cpp/variant/utility_functions.hpp> //print miatt
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <cmath> //fmod miatt

using namespace godot; //Ha nem akarod odatenni minden sor ele hogy godot:: xd

Ball::Ball() {} //Konstruktor
Ball::~Ball() {} //Destruktor

void Ball::_bind_methods() { //Azert hogy a godot tudja hasznalni a fuggvenyeket
	
}

void Ball::_ready() { //amikor elindul a program
	// 1) Try to find BallParent as the tree parent
	if (auto p = Object::cast_to<BallParent>(get_parent())) { //megkeressuk a ball parentjet, hogy BallParent tipusu-e
		ball_parent = p; //ha igen, akkor eltesszuk egy valtozoba
		UtilityFunctions::print("Ball::_ready: found BallParent via get_parent()"); //kiirjuk hogy megtalaltuk
	}
	else { //ha nem talaltuk meg igy
		// 2) Fallback: try to find a node named "BallParent" in the current scene root
		if (auto root = get_tree()->get_current_scene()) { //lekerni a jelenlegi scene gyokeret
			ball_parent = Object::cast_to<BallParent>(root->get_node_or_null("BallParent")); //megkeressuk a BallParent node-ot a scene gyokerben
			if (ball_parent) UtilityFunctions::print("Ball::_ready: found BallParent in scene root"); //ha megtalaltuk, kiirjuk
		}
	}

	// Find Player: try relative path first, then scene root
	player = Object::cast_to<Player>(get_node_or_null("../Player")); //megprobaljuk a Player node-ot megtalalni a Ball szuloje alatt
	if (!player) { //ha nem talaltuk meg igy
		if (auto root = get_tree()->get_current_scene()) {  //lekerni a jelenlegi scene gyokeret
			player = Object::cast_to<Player>(root->get_node_or_null("Player"));		//megkeressuk a Player node-ot a scene gyokerben
		}
	}

	UtilityFunctions::print(String("Ball::_ready: player ") + (player ? "found" : "not found")); //kiirjuk hogy megtalaltuk-e a playert
}

void Ball::_process(double delta) { //minden frameben lefut
	// ha nincs se ballparent se player, akkor nem csinalunk semmit
	if (!ball_parent && !player) {
		return;
	}

	elapsed += delta * speed; //eltelt ido
	//ping pong effektus szamitas
	double phase = fmod(elapsed, 2.0);  // fmod a maradekos osztast csinalja
	double alpha = (phase < 1.0) ? phase : (2.0 - phase); //ha phase kisebb mint 1, akkor alpha = phase, egyebkent alpha = 2 - phase (igy lesz ping-pong effektus)
	//megszerezzuk a ballparent es a player poziciojat
	Vector2 a = ball_parent ? ball_parent->get_global_position() : get_global_position(); //ha van ballparent, akkor annak a pozicioja, egyebkent a sajat pozicioja
	Vector2 b = player ? player->get_global_position() : a; //ha van player, akkor annak a pozicioja, egyebkent a ballparent pozicioja (igy nem mozdul el a ball, ha nincs player)

	// move the Ball smoothly between a and b
	set_global_position(a.lerp(b, static_cast<real_t>(alpha))); //elmozgatjuk a ballt a ket pozicio kozott lerp segitsegevel (linear interpolation)
}
/* mindez nem tudom mi, kedves chatgpt irta nekem <3*/