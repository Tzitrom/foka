#pragma once//minden header elején legyen ott pls

#include <godot_cpp/classes/character_body2d.hpp>  //meghatározza a karakterünk típusát godotban, ebben az esetben CharacterBody2D


namespace godot { //mintha using namespace godot; lenne, viszont csak a {}-on belül érvényes

	class Player : public CharacterBody2D { //A Player osztály a CharacterBody2D osztályból származik
		GDCLASS(Player, CharacterBody2D) //Ez egy makró, ami egy rakat kód röviden, hogy a godot értse, hogy ez egy CharacterBody2D típusú osztály

    private:  //privát
        double gravity; //gravitáció
		bool jump_possible;  //felesleges
		int count = 0; //ugrás számláló (felesleges)
    protected:
		static void _bind_methods();  //Azért hogy a godot tudja használni a függvényeket

    public:
		Player();  //Konstruktor
		~Player(); //Destruktor 

		void _process(double delta);  //Ez az alap godot függvény, ami minden frameben lefut. a delta az eltelt idõ az elõzõ frame óta
		void jump(); //ugrás függvény
		void _ready() override; //Ez alap godot függvény, ami akkor fut le, amikor a karakterünk bejön a képbe, magyarul amikor elindul a program
    };
}