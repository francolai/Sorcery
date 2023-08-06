#include "card.h"
#include <memory>
#include "player.h"
#include <string>
#include "effect.h"

using namespace std;

//constructor
Card::Card(string name, int cost, shared_ptr<Effect> ability) :
	name{name}, cost{cost}, ability{ability} {}


// accessors
string Card::get_name() {
	return name;
}

int Card::get_cost() {
	return cost;
}

shared_ptr<Effect> Card::get_ability() {
	return ability;
}
