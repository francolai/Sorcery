#include "enchantmenteffect.h"
#include <string>

using namespace std;

static const string NeedTarget = "Enchantment can only be used on a minion.";

void EnchantmentEffect::activate(Player &whoactivated, int cost) {
	throw NeedTarget;
}

void EnchantmentEffect::activate(Player &whoactivated, Player &targetP, shared_ptr<Ritual> target, int cost) {
	throw NeedTarget;
}
