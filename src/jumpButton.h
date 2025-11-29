#pragma once//minden header elejen legyen ott

#include <godot_cpp/classes/button.hpp>  //meghatarozza a jumpButton tipusat godotban, ebben az esetben Button

using namespace godot;  //Ha nem akarod odatenni minden sor ele hogy godot:: xd

class jumpButton : public Button { //A jumpButton osztaly a Button osztalybol szarmazik
	GDCLASS(jumpButton, Button) //Ez egy makro, ami egy rakat kod roviden, hogy a godot ertse, hogy ez egy Button tipusu osztaly

protected:
	static void _bind_methods(); //Azert hogy a godot tudja hasznalni a fuggvenyeket
public:
	void jumpEmit(); //felesleges
	void testprint(); //ures :(
	void print(); //tesztkiiras
	void _process(double delta) override; //Minden frameben meghivodik

private:
	bool is_pressed = false; //A gomb lenyomva van-e
};
