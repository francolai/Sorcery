#ifndef effect_h
#define effect_h
#include <memory>

class Player;
class Attackable;
class Ritual;
class Minion;

class Effect {
	public:
	virtual void activate(Player &whoactivated, int cost) = 0;
	virtual void activate(Player &whoactivated, Player &targetP, 
				std::shared_ptr<Attackable> target, int cost) = 0;
	virtual void activate(Player &whoactivated, Player &targetP, 
				std::shared_ptr<Ritual> target, int cost) = 0;
	virtual void start_turn_trigger(Player &active);
	virtual void end_turn_trigger(Player &active);
	virtual void enter_play_trigger(Player &whoplayed, Player &whoowned, std::shared_ptr<Minion> whoentered);
	virtual void attack_player_trigger(std::shared_ptr<Minion> whoattacked, Player &whogetsattacked);
	virtual void enchant(std::shared_ptr<Minion> m) {}
};


#endif
