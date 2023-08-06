#include "deck.h"
#include "card.h"
#include <memory>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

// add a card c to the deck
void Deck::add_card(shared_ptr<Card> c) {
	stackofCards.emplace_back(c);
}

// add a card c to the bottom of the deck
void Deck::add_card_bottom(shared_ptr<Card> c) {
	stackofCards.insert(stackofCards.begin(), c);
}

// shuffle the deck
void Deck::shuffle() { // using random module
	srand(time(NULL));
	for (int i = stackofCards.size(); i > 0; --i) {
		int num_generated = rand() % i;
		auto card_chosen = stackofCards.at(num_generated);
		stackofCards.erase(stackofCards.begin() + num_generated);
		stackofCards.emplace_back(card_chosen);
	}
}
	

// draw a card from the deck. If no card is available, throws an exception.
shared_ptr<Card> Deck::draw() {
	if (stackofCards.size() == 0) {
		throw DeckisEmpty{};
	}
	else {
		auto card_drawn = stackofCards.back();
		stackofCards.pop_back();
		return card_drawn;
	}
}


