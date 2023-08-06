#include "activatedabilitydata.h"
#include "player.h"
#include <memory>
#include "carddata.h"
#include <string>
#include "attackable.h"
#include "ritual.h"
#include "enchantment.h"
#include "minion.h"

using namespace std;

static const string Unavailable = "Cannot activate ability.";
		

//NO ABILITY
void NoAbility::activate(Player &whoactivated, int cost) {
	throw Unavailable;
}
	
void NoAbility::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target, int cost) {
	throw Unavailable;
}

void NoAbility::activate(Player &whoactivated, Player &targetP, shared_ptr<Ritual> target, int cost) {
	throw Unavailable;
}


//NOVICE PYROMANCER ABILITY
void NovicePyromancerE::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target, int cost) {
	try{
		whoactivated.consumes_magic(cost); // could throw errormsg.
		target->receiveattack(1);
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}

// APPRENTICE SUMMONER ABILITY
void ApprenticeSummonerE::activate(Player &whoactivated, int cost) {
	if (whoactivated.num_playing() >= 5) {
		throw "The board is fulled, cannot activate.";
	}
	else {
		try {
			whoactivated.consumes_magic(cost); //could throw errormsg
			int minion_summoned = 0;
			while (minion_summoned != 1) {
				if (whoactivated.num_playing() >= 5) {
					break;
				}
				shared_ptr<Minion> nm = static_pointer_cast<Minion> (construct_card("Air Elemental"));
				whoactivated.set_play(nm, false);		
				++minion_summoned;
			}
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
}	


// MASTER SUMMONER ABILITY
void MasterSummonerE::activate(Player &whoactivated, int cost) {
	if (whoactivated.num_playing() >= 5) {
		throw "Maximum playing cards reached, cannot activate.";
	}
	else {
		try {
			whoactivated.consumes_magic(cost); //could throw errormsg
			int minion_summoned = 0;
			while (minion_summoned != 3) {
				if (whoactivated.num_playing() >= 5) {
					break;
				}
				shared_ptr<Minion> nm = static_pointer_cast<Minion> (construct_card("Air Elemental"));
				whoactivated.set_play(nm, false);		
				++minion_summoned;
			}
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
}	

// LITTLE HERO ABILITY
void LittleHeroE::activate(Player &whoactivated, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg
		(whoactivated.get_opponent())->receiveattack(5);
	}
	catch (char const *&ErrorMsg) {
			throw ErrorMsg;
	}
}

// BANISH ABILITY
void BanishE::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg.
		targetP.remove_play(target->get_pos());
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}

void BanishE::activate(Player &whoactivated, Player &targetP, shared_ptr<Ritual> target, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg.
		targetP.remove_ritual();
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}


// UNSUMMON ABILITY
void UnsummonE::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg
		targetP.remove_play(target->get_pos());
		targetP.get_deck().add_card_bottom(target);
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}


// RECHARGE ABILITY
void RechargeE::activate(Player &whoactivated, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg
		(whoactivated.get_ritual())->modify_charge(3);
	}
	catch (char const *ErrorMsg) {
		throw ErrorMsg;
	}		
}

// DISENCHANT ABILITY
void DisenchantE::activate(Player &whoactivated, Player &targetP, shared_ptr<Attackable> target, int cost) {
	if (dynamic_pointer_cast<Minion>(target)) {
		throw "Cannot disenchant a minion without enchantment.";
	}
	else {
		try {
			whoactivated.consumes_magic(cost); // could throw errormsg.
			shared_ptr<Enchantment> ep = dynamic_pointer_cast<Enchantment>(target);
			shared_ptr<Attackable> minion_after_disenchant = ep->get_component();
			shared_ptr<Minion> minion_only = minion_after_disenchant->get_minion();
			minion_after_disenchant->modify(minion_only);
			targetP.replace_play(minion_after_disenchant->get_pos(), minion_after_disenchant);
		}
		catch (char const *ErrorMsg) {
			throw ErrorMsg;
		}
	}
}

// RAISEDEAD ABILITY
void RaiseDeadE::activate(Player &whoactivated, int cost) {
	int num_dead = whoactivated.get_grave().size();
	if (num_dead == 0) {
		throw "Nothing to be resurrected!";
	}
	else if (whoactivated.num_playing() >= 5) {
		throw "Maximum playing cards reached, cannot resurrect the dead.";
	}
	else {
		try {
			whoactivated.consumes_magic(cost); // could throw errormsg.
			shared_ptr<Minion> resurrected = whoactivated.get_grave().back();
			whoactivated.get_grave().pop_back();
			whoactivated.set_play(resurrected, false);
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
}
			
// BLIZZARD ABILITY
void BlizzardE::activate(Player &whoactivated, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg
		for (auto &activeplaying : whoactivated.get_playing()) {
			activeplaying->receiveattack(2);
		}
		for (auto &non_activeplaying : (whoactivated.get_opponent())->get_playing()) {
			non_activeplaying->receiveattack(2);
		}
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}

// DrawACard ABILITY
void DrawACard::activate(Player &whoactivated, int cost) {
	int original_magic = whoactivated.get_magic();
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg
		whoactivated.draw_a_card();
	}
	catch (char const *&ErrorMsg) {
		// if magic is consumed but no card is drawn.
		if (original_magic != whoactivated.get_magic()) {
			whoactivated.consumes_magic(-cost);
		}
		throw ErrorMsg;
	}
}

// GIFT ABILITY
void GiftE::activate(Player &whoactivated, int cost) {
	try {
		whoactivated.consumes_magic(cost); // could throw errormsg
		whoactivated.consumes_magic(-3);
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}



