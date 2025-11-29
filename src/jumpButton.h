#pragma once//minden header elején legyen ott

#include <godot_cpp/classes/button.hpp>  //meghatározza a jumpButton típusát godotban, ebben az esetben Button

using namespace godot;  //Ha nem akarod odatenni minden sor elé hogy godot:: xd

class jumpButton : public Button { //A jumpButton osztály a Button osztályból származik
	GDCLASS(jumpButton, Button) //Ez egy makró, ami egy rakat kód röviden, hogy a godot értse, hogy ez egy Button típusú osztály

protected:
	static void _bind_methods(); //Azért hogy a godot tudja használni a függvényeket
public:
	void jumpEmit(); //felesleges
	void testprint(); //üres :(
	void print(); //tesztkiírás
	void _process(double delta) override; //Minden frameben meghívódik

private:
	bool is_pressed = false; //A gomb lenyomva van-e
};
