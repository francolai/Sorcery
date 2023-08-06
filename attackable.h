#ifndef attackable_h
#define attackable_h
#include "card.h"
#include <memory>
#include "player.h"

class Effect;
class Minion;

class Attackable : public Card {
	int pos;
	public:
	Attackable(std::string name, int cost, std::shared_ptr<Effect> ability);
	void set_pos(int pos); // set the current position of the card.
	int get_pos(); // get the current position of the card.

	virtual void attack(std::shared_ptr<Attackable> target) = 0;
	virtual void attack(Player &other) = 0;
	virtual void receiveattack(int i) = 0;
	virtual bool isDead() = 0;
	virtual bool exhausted() = 0;
	virtual void reset_action() = 0;
	virtual void modifyaction() = 0;
	virtual std::shared_ptr<Minion> get_minion() = 0;
	virtual void reset_state(bool dead = false) = 0;
	virtual void modify(std::shared_ptr<Minion> m) = 0;
	virtual std::shared_ptr<Attackable> get_component();
};

#endif
