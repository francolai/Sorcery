#include "hand.h"
#include "card.h"
#include <memory>
#include <vector>

using namespace std;

// add card to the hand
void Hand::add_card(shared_ptr<Card> c) {
	holding_cards.emplace_back(c);
}

// remove card from the hand
void Hand::remove_card(int i) {
	holding_cards.erase(holding_cards.begin() + i);
}

// return the card i from the hand
shared_ptr<Card> Hand::play_card(int i) {
	auto card_playing = holding_cards.at(i);
	return card_playing;
}

// check if the hand is full
bool Hand::isFull() {
	return (holding_cards.size() >= max_size);
}


// return the number of cards in the hand
int Hand::size() {
	return holding_cards.size();
}	

// return the vector of holding cards
vector<shared_ptr<Card>> &Hand::get_holding() {
	return holding_cards;
}

