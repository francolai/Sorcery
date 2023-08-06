#ifndef triggerabilitydata_h
#define triggerabilitydata_h
#include "triggereffect.h"
#include <memory>

class Player;
class Minion;

class FireElementalE: public TriggerEffect {
	public:
	void enter_play_trigger(Player &whoplayed, Player &whoowned, std::shared_ptr<Minion> whoentered) override;
};

class DarkRitualE : public TriggerEffect {
	public:
	void start_turn_trigger(Player &active) override;
};

class PotionSellerE : public TriggerEffect {
	public:
	void end_turn_trigger(Player &active) override;
};

class AuraOfPowerE: public TriggerEffect {
	public:
	void enter_play_trigger(Player &whoplayed, Player &whoowned, std::shared_ptr<Minion> whoentered) override;
};

class StandstillE : public TriggerEffect {
	public:
	void enter_play_trigger(Player &whoplayed, Player &whoowned, std::shared_ptr<Minion> whoentered) override;
};
