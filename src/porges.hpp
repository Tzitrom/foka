#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>
using namespace godot;

class Gomb: public Control
{
	GDCLASS(Gomb, Control)
protected:
	static void _bind_methods();
private:
	int szog;
	Button* host_button = nullptr;
	void setSzog(int alfa);
	void kiir();
	void testkys();
	void _ready() override;
};