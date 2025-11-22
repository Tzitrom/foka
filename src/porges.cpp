#include "porges.hpp"
#include <godot_cpp/core/print_string.hpp>

using namespace godot;

void Gomb::setSzog(int alfa)
{
	alfa = szog;
}

void Gomb::kiir()
{
	print_line("anyad");
}

void Gomb::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("kiir"), &Gomb::kiir);
	ClassDB::bind_method(D_METHOD("ready"), &Gomb::_ready);
}

void Gomb::testkys() {
	UtilityFunctions::print("öld meg magad");
}

void Gomb::_ready()
{
	host_button = get_node<Button>("Gomg");
	(Error)host_button->connect("pressed", Callable(this, "testkys"));
}
