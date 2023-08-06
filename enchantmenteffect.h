#ifndef enchantmenteffect_h
#define enchantmenteffect_h
#include "effect.h"
#include <memory>

class Player;
class Attackable;
class Ritual;
class Minion;

class EnchantmentEffect: public Effect{
	public:
	void activate(Player &whoactivated, int cost) override;
	void activate(Player &whoactivated, Player &targetP, 
			std::shared_ptr<Ritual> target, int cost) override;
	virtual void enchant(std::shared_ptr<Minion> m) = 0;
};

#endif
