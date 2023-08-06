#include "triggerabilitydata.h"
#include <memory>
#include "player.h"
#include "minion.h"

// FIRE ELEMENTAL ABILITY
void FireElementalE::enter_play_trigger(Player &whoplayed, Player &whoowned, shared_ptr<Minion> whoentered) {
	if (&whoplayed != &whoowned) {
		whoentered->receiveattack(1);
	}
}
		
	
// DARK RITUAL ABILITY
void DarkRitualE::start_turn_trigger(Player &active) {
	try {
		(active.playing_ritual)->expend_charge(1);
		++active.magic;
	}
	catch (string &ErrorMsg) {}
}

// POTION SELLER ABILITY
void PotionSellerE::end_turn_trigger(Player &active) {
	for (auto &playing : active.playing_cards()) {
		playing->receiveattack(-1);
	}
}

// AURA OF POWER ABILITY
void AuraOfPowerE::enter_play_trigger(Player &whoplayed, Player &whoowned, shared_ptr<Minion> whoentered) {
	if (&whoplayed == &whoowned) {
		try {
			(whoowned.playing_ritual)->expend_charge(1);
			whoentered->modifyattack(1);
			whoentered->receiveattack(-1);
		}
		catch (string &ErrorMsg) {}
	}
}

// STANDSTILL ABILITY
void StandstillE::enter_play_trigger(Player &whoplayed, Player &whoowned, shared_ptr<Minion> whoentered) {
	try {
		(whoowned.playing_ritual)->expend_charge(2);
		whoplayed.remove_play(whoentered->get_pos());
	}
	catch (string &ErrorMsg) {}
}