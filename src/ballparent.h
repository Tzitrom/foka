#pragma once //minden header elejen legyen ott pls

#include <godot_cpp/classes/character_body2d.hpp>  //meghatarozza a karakterunk tipusat godotban, ebben az esetben CharacterBody2D
#include <godot_cpp/classes/sprite2d.hpp>  //sprite2d osztaly, hogy kezelni tudjuk a karakter texturajat

using namespace godot;

class BallParent : public CharacterBody2D {
	GDCLASS(BallParent, CharacterBody2D)
protected:
	static void _bind_methods();
public:
	BallParent();
	~BallParent();

	void _ready() override;
	void _process(double delta) override;
};