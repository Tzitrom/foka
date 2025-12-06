#include "ball.h" //Azert hogy lassuk a ball.h tartalmat
#include "ballparent.h" //Hogy lassa a BallParent osztalyt
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
	// 1) Try to find BallParent as the tree parent
	if (auto p = Object::cast_to<BallParent>(get_parent())) { //megkeressuk a ball szulojet, hogy BallParent tipusu-e
		ball_parent = p; //ha igen, akkor eltesszuk egy valtozoba
		// UtilityFunctions::print("Ball::_ready: found BallParent via get_parent()"); //kiirjuk hogy megtalaltuk
	}
	else { //ha nem talaltuk meg igy
		// 2) Fallback: try to find a node named "BallParent" in the current scene root
		if (auto root = get_tree()->get_current_scene()) { //lekerni a jelenlegi scene gyokeret
			ball_parent = Object::cast_to<BallParent>(root->get_node_or_null("BallParent")); //megkeressuk a BallParent node-ot a scene gyokerben
			// if (ball_parent) UtilityFunctions::print("Ball::_ready: found BallParent in scene root"); //ha megtalaltuk, kiirjuk
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


void Ball::_process(double delta) {
    // 1. If not moving yet, check for shoot
    if (!moving) {

        if (Input::get_singleton()->is_action_just_pressed("loves")) {

            // Get start and end positions ONCE
            start_pos = player->get_global_position();
            target_pos = ball_parent->get_global_mouse_position();

            t = 0.0;
            moving = true;

            // Teleport the ball to player instantly at the start
            set_global_position(start_pos);
        }

        return; // don't move if not moving
    }

    // 2. If moving, advance progress
    t += speed * delta;   // speed should be small, e.g. 0.5 or 1.0

    // 3. When the projectile reaches its target, stop moving
    if (t >= 1.0) {
        t = 1.0;
        moving = false;
    }

    // 4. Move between start_pos -> target_pos
    Vector2 new_pos = start_pos.lerp(target_pos, static_cast<real_t>(t));
    set_global_position(new_pos);
}
