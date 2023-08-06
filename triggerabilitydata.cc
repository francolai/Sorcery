#include "triggerabilitydata.h"
#include <memory>
#include "player.h"
#include "minion.h"
#include "ritual.h"
#include <iostream>

using namespace std;

// FIRE ELEMENTAL ABILITY
void FireElementalE::enter_play_trigger(Player &whoplayed, Player &whoowned, shared_ptr<Minion> whoentered) {
	if (&whoplayed != &whoowned) {
		whoentered->receiveattack(1);
	}
}
		
	
// DARK RITUAL ABILITY
void DarkRitualE::start_turn_trigger(Player &active) {
	try {
		active.get_ritual()->expend_charge(1);
		cout << active.get_name() << " gets 1 magic from Dark Ritual!" << endl;
		active.consumes_magic(-1);
	}
	catch (char const *&ErrorMsg) {
		cout << ErrorMsg << endl;
	}
}

// POTION SELLER ABILITY
void PotionSellerE::end_turn_trigger(Player &active) {
	for (auto &playing : active.get_playing()) {
		(dynamic_pointer_cast<Minion>(playing))->modifydefence(1);
		cout << playing->get_name() << " gets 1 defence from Potion Seller!" << endl;
	}
}

// AURA OF POWER ABILITY
void AuraOfPowerE::enter_play_trigger(Player &whoplayed, Player &whoowned, shared_ptr<Minion> whoentered) {
	if (&whoplayed == &whoowned) {
		try {
			whoowned.get_ritual()->expend_charge(1);
			whoentered->modifyattack(1);
			whoentered->modifydefence(1);
			cout << whoentered->get_name() << 
				" gets 1 attack and 1 defence from Aura of Power!" << endl;
		}
		catch (char const *&ErrorMsg) {
			cout << ErrorMsg << endl;
		}
	}
}

// STANDSTILL ABILITY
void StandstillE::enter_play_trigger(Player &whoplayed, Player &whoowned, shared_ptr<Minion> whoentered) {
	try {
		whoowned.get_ritual()->expend_charge(2);
		whoplayed.remove_play(whoentered->get_pos());
		cout << whoentered->get_name() << " gets destroyed by Standstill!" << endl;
	}
	catch (char const *&ErrorMsg) {
		cout << ErrorMsg << endl;
	}
}

// SHIELD ABILITY
void ShieldE::attack_player_trigger(std::shared_ptr<Minion> whoattacked, Player &whogetsattacked) {
	try {
		whogetsattacked.get_ritual()->expend_charge(2);
		int shield_value = whoattacked->get_atk();
		whogetsattacked.receiveattack(-shield_value);
		cout << "Shield activated!" << endl;
	}
	catch (char const *&ErrorMsg) {
		cout << ErrorMsg << endl;
	}
}

