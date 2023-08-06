#ifndef spell_h
#define spell_h
#include "card.h"
#include <memory>
#include <string>

class Effect;

class Spell : public Card {
	public:
	Spell(std::string name, int cost, std::shared_ptr<Effect> ability);

	void play(Player &whoplayed) override;
};

#endif
