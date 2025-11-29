#pragma once//minden header elejen legyen ott pls

#include <godot_cpp/classes/character_body2d.hpp>  //meghatarozza a karakterunk tipusat godotban, ebben az esetben CharacterBody2D


namespace godot { //mintha using namespace godot; lenne, viszont csak a {}-on belul ervenyes

	class Player : public CharacterBody2D { //A Player osztaly a CharacterBody2D osztalybol szarmazik
		GDCLASS(Player, CharacterBody2D) //Ez egy makro, ami egy rakat kod roviden, hogy a godot ertse, hogy ez egy CharacterBody2D tipusu osztaly

    private:  //privat
        double gravity; //gravitacio
		bool jump_possible;  //felesleges
		int count = 0; //ugras szamlalo (felesleges)
		const float SPEED = 10; //milyen gyorsan gyorsul a karakter vizszintesen a MAX_SPEED-ig
		const float JUMP_SIZE = -400; //vitathato, kiserletezzunk
		const float MAX_SPEED = 500; //max vizszintes speed (ennel lehet egy kicsit gyorsabb, kiserletezzunk
    protected:
		static void _bind_methods();  //Azert hogy a godot tudja hasznalni a fuggvenyeket

    public:
		Player();  //Konstruktor
		~Player(); //Destruktor 

		void _process(double delta);  //Ez az alap godot fuggveny, ami minden frameben lefut. a delta az eltelt ido az elozo frame ota
		void jump(); //ugras fuggveny
		void _ready() override; //Ez alap godot fuggveny, ami akkor fut le, amikor a karakterunk bejon a kepbe, magyarul amikor elindul a program
		void move();
    };
}