#include "spell.h"
#include <memory>
#include <string>
#include <iostream>
#include "effect.h"

using namespace std;

//constructor
Spell::Spell(string name, int cost, shared_ptr<Effect> ability) :
	Card {name, cost, ability} {}


// play from hand, activate the effect of the spell, throw an error message if unsuccesful (since the spell needs a target)
void Spell::play(Player &whoplayed) {
	try {
		get_ability()->activate(whoplayed, get_cost());
	}
	catch (string &ErrorMsg) {
		throw ErrorMsg;
	} 
}	
