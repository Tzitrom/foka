#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>
using namespace godot;

class Gomb: public Control
{
	GDCLASS(Gomb, Control)
public:
	void _ready() override;
protected:
	static void _bind_methods();
private:
	Button* host_button = nullptr;
	void testkys();
	
};