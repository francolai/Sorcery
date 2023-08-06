#include "attackable.h"
#include <memory>
#include <iostream>
#include "player.h"

using namespace std;

//constructor
Attackable::Attackable(string name, int cost, shared_ptr<Effect> ability) :
	Card{name, cost, ability}, pos{-1} {}


// set the current position of the card.
void Attackable::set_pos(int pos) {
	this->pos = pos;
}

// return the current position of the card.
int Attackable::get_pos() {
	return pos;
}

shared_ptr<Attackable> Attackable::get_component() {
	return nullptr;
}
