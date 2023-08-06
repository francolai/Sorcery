#include "triggereffect.h"
#include <string>

using namespace std;

static const string NoActivateTrigger = "Trigger ability cannot be actively casted.";

void TriggerEffect::activate(Player &whoactivated, int cost) {
	throw NoActivateTrigger;
}

void TriggerEffect::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target, int cost) {
	throw NoActivateTrigger;
}

void TriggerEffect::activate(Player &whoactivated, Player &targetP, shared_ptr<Ritual> target, int cost) {
	throw NoActivateTrigger;
}

