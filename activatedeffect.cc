#include "activatedeffect.h"
#include <string>

using namespace std;

static const string TargetRequired = "Requires a target.";
static const string NoMinion = "Cannot activate on the minion.";
static const string NoRitual = "Cannot activate on the ritual.";

// Default method, overridable.
void ActivatedEffect::activate(Player &whoactivated, int cost) {
	throw TargetRequired;
}

void ActivatedEffect::activate(Player &whoactivated, Player &targetP, 
				shared_ptr<Attackable> target, int cost) {
	throw NoMinion;
}

void ActivatedEffect::activate(Player &whoactivated, Player &targetP, 
				shared_ptr<Ritual> target, int cost) {
	throw NoRitual;
}

