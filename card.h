#ifndef card_h
#define card_h
#include <string>
#include <memory>
#include <iostream>
#include "player.h"

class Effect;

class Card {
	protected:
	std::string name;
	int cost;
	std::shared_ptr<Effect> ability;
	public:
	Card(std::string name, int cost, std::shared_ptr<Effect> ability);

	virtual void play(Player &whoplayed) = 0;
	friend std::ostream &operator<<(std::ostream &out, Card &c);

	std::string get_name();
	int get_cost();
	virtual std::shared_ptr<Effect> get_ability();
};

#endif
