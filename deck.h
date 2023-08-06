#ifndef deck_h
#define deck_h
#include <vector>
#include <memory>

class Card;

class DeckisEmpty{};
class Deck {
	std::vector<std::shared_ptr<Card>> stackofCards;
	public:
	void add_card(std::shared_ptr<Card> c);
	void add_card_bottom(std::shared_ptr<Card> c);
	void shuffle();
	std::shared_ptr<Card> draw();
};

#endif
