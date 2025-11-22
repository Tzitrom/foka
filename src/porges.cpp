#include "porges.hpp"
#include <godot_cpp/core/print_string.hpp>

using namespace godot;

void Gomb::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("testkys"), &Gomb::testkys);
	ClassDB::bind_method(D_METHOD("_ready"), &Gomb::_ready);
}

void Gomb::testkys() {
	UtilityFunctions::print("test test test");
}

void Gomb::_ready()
{
	host_button = get_node<Button>("Gomg");
	(Error)host_button->connect("pressed", Callable(this, "testkys"));
}
