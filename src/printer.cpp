#include "printer.h"
#include "player.h"

Printer::Printer()
{
	text = "";
}

Printer::~Printer() {
}

void Printer::_get_text() {
	Label::set_text()
}

void Printer::_set_text() {
	(Error)get_node<CharacterBody2D>("Player")->connect("send_text", Callable(this, ))
}
