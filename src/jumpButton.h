#pragma once

#include <godot_cpp/classes/button.hpp>

using namespace godot;

class jumpButton : public Button {
	GDCLASS(jumpButton, Button)

protected:
	static void _bind_methods();
public:
	void jumpEmit();
	void testprint();
	void print();
	void _process(double delta) override;

private:
	bool is_pressed = false;
};
