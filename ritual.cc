#include "ritual.h"
#include <memory>

using namespace std;

// constructor
Ritual::Ritual(std::string name, int cost, std::shared_ptr<Effect> ability, int charge) :
	Card {name, cost, ability}, charge{charge} {}

// play the ritual
void Ritual::play(Player &whoplayed) {
	whoplayed.set_ritual(shared_from_this());
}

// modify the charge
void Ritual::modify_charge(int i) {
	charge += i;
}


// deduct the charge if the charge is not 0, otherwise an error message is thrown.
void Ritual::expend_charge(int i) {
	if (charge - i < 0) {
		throw "The Ritual does not have enough charge";
	}
	else {
		charge -= i;
	}	
}

int Ritual::get_charge() {
	return charge;
}
	
