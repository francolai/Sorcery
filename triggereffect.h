#ifndef triggereffect_h
#define triggereffect_h
#include "effect.h"
#include <memory>

class Player;
class Attackable;
class Ritual;

class TriggerEffect: public Effect{
	public:
	void activate(Player &whoactivated, int cost) override;
	void activate(Player &whoactivated, Player &targetP, 
			std::shared_ptr<Attackable> target, int cost) override;
	void activate(Player &whoactivated, Player &targetP, 
			std::shared_ptr<Ritual> target, int cost) override;
};

#endif

