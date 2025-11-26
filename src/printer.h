#pragma once

#include <godot_cpp/classes/label.hpp>

using namespace godot;

class Printer : public Label {
	GDCLASS (Printer, Label)

protected:
	static void _bind_methods();
private:
	std::string text;
public:
	Printer();
	~Printer();

	void _get_text();
	void _set_text();
};