#ifndef ritual_h
#define ritual_h
#include "card.h"
#include <memory>

class Ritual : public Card, public std::enable_shared_from_this<Ritual> {
	int charge;
	public:
	Ritual(std::string name, int cost, std::shared_ptr<Effect> ability, int charge);

	void play(Player &whoplayed) override;
	void modify_charge(int i); // if i is negative, subtract charge, otherwise add charge.
	void expend_charge(int i);
	int get_charge();
};

#endif
