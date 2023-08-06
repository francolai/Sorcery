#ifndef activatedeffect_h
#define activatedeffect_h
#include "effect.h"

class Player;
class Attackable;
class Ritual;

class ActivatedEffect: public Effect {
	public:
	virtual void activate(Player &whoactivated, int cost) override;
	virtual void activate(Player &whoactivated, Player &targetP, 
				std::shared_ptr<Attackable> target, int cost) override;
	virtual void activate(Player &whoactivated, Player &targetP, 
				std::shared_ptr<Ritual> target, int cost) override;
};

#endif
