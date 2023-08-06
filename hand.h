#ifndef hand_h
#define hand_h
#include <memory>
#include <vector>

class Card;

const int max_size = 5;

class Hand {
	std::vector<std::shared_ptr<Card>> holding_cards;
	public:
	void add_card(std::shared_ptr<Card> c);
	void remove_card(int i);
	std::shared_ptr<Card> play_card(int i);
	bool isFull();
	int size();
	std::vector<std::shared_ptr<Card>> &get_holding();
	friend std::ostream &operator<<(std::ostream &out, Hand &h);
};

#endif
