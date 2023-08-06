#include "enchantmentabilitydata.h"
#include <memory>
#include "carddata.h"
#include <string>
#include "player.h"
#include "minion.h"
#include "attackable.h"
#include "activatedabilitydata.h"
#include "enchantment.h"

using namespace std;

// place the enchantment e on the target minion and update the status.
static void attach_and_modify(Player &whoactivated, string enchant_name, shared_ptr<Attackable> target, int cost);
	

//GIANT STRENGTH ABILITY
void GiantStrengthE::enchant(shared_ptr<Minion> m) {
	m->modifyattack(2);
	m->modifydefence(2);
}

void GiantStrengthE::activate(Player &whoactivated, Player &targetP, 
				shared_ptr<Attackable> target, int cost) {
	try {
		attach_and_modify(whoactivated, "Giant Strength", target, cost);
	}
	catch (char const * &ErrorMsg) {
		throw ErrorMsg;
	}
}


// MAGIC FATIGUE ABILITY
void MagicFatigueE::enchant(shared_ptr<Minion> m) {
	m->modify_active_cost(2);
}

void MagicFatigueE::activate(Player &whoactivated, Player &targetP, 
				shared_ptr<Attackable> target, int cost) {
	try {
		attach_and_modify(whoactivated, "Magic Fatigue", target, cost);
	}
	catch (char const * &ErrorMsg) {
		throw ErrorMsg;
	}
}

// SILENCE ABILITY
void SilenceE::enchant(shared_ptr<Minion> m) {
	shared_ptr<Effect> noabilitycopy = make_shared<NoAbility>();
	m->modifyability(noabilitycopy);
}

void SilenceE::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target,
				int cost) {
	try {
		attach_and_modify(whoactivated, "Silence", target, cost);
	}
	catch (char const * &ErrorMsg) {
		throw ErrorMsg;
	}
}

// EXTRA DRAW ABILITY
void ExtraDrawE::enchant(shared_ptr<Minion> m) {
	shared_ptr<Effect> drawacardabilitycopy = make_shared<DrawACard>();
	int original_cost = m->get_active_cost();
	int cost_modifying = original_cost - 1;
	m->modify_active_cost(-cost_modifying);
	m->modifyability(drawacardabilitycopy);
}

void ExtraDrawE::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target,
				int cost) {
	try {
		attach_and_modify(whoactivated, "Extra Draw", target, cost);
	}
	catch (char const * &ErrorMsg) {
		throw ErrorMsg;
	}
}


// place the enchantment e on the target minion and update the status.
static void attach_and_modify(Player &whoactivated, string enchant_name, shared_ptr<Attackable> target, int cost) {
	try {
		whoactivated.consumes_magic(cost); // can throw errormsg.
		shared_ptr<Enchantment> copy = 
				static_pointer_cast<Enchantment>(construct_card(enchant_name));
		copy->attach(target);
		shared_ptr<Minion> minion_only = target->get_minion();
		copy->modify(minion_only);
		whoactivated.replace_play(target->get_pos(), copy);
	}
	catch (char const * &ErrorMsg) {
		throw ErrorMsg;
	}
}
	
	