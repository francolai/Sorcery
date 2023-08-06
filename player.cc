#include <iostream>
#include <fstream>
#include <memory>
#include "player.h"
#include "deck.h"
#include "hand.h"
#include "card.h"
#include "minion.h"
#include "attackable.h"
#include "ritual.h"
#include "carddata.h"
#include "triggerabilitydata.h"
#include "ascii_graphics.h"

using namespace std;

// load the deck from the filename
unique_ptr<Deck> Player::load_deck(string filename) {
	ifstream infile(filename);
	unique_ptr<Deck> d = make_unique<Deck>();
	string card_name;
	while (getline(infile, card_name)) {
		try {
			shared_ptr<Card> c = construct_card(card_name);
			d->add_card_bottom(c);
		}
		catch (char const * &ErrorMsg) {
			cout << ErrorMsg << " " << card_name << endl;
		}
	}
	return d;
}
				
// initialize the player with name, and deck loaded from filename.
void Player::init(string name, string filename, bool test_mode, Player *opponent) {
	this->name = name;
	this->health = init_health;
	this->magic = init_magic;	
	this->d = load_deck(filename);
	this->test_mode = test_mode;
	this->opponent = opponent;
	this->playing_ritual = nullptr;
	if (!test_mode) {
		d->shuffle();
	}
	h = make_unique<Hand>();
	try {
		for (int i = 0; i < 4; ++i) {
			h->add_card(d->draw()); // could throw errormsg.
		}
	}
	catch (DeckisEmpty &e) {
		cout << name << " only have " << h->size(); 
		cout <<" cards because the deck is already emptied";
		cout << endl;
	}
}

// start the turn
void Player::start_turn() {
	cout << "This is now " << name << "'s turn!" << endl;
	++magic;
	try {
		draw_a_card();
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
	// activate trigger effect
	for (auto &active_playing : playing_cards) {
		active_playing->get_ability()->start_turn_trigger(*this);
	}
	if (playing_ritual) {
		playing_ritual->get_ability()->start_turn_trigger(*this);
	}
}


// end the turn
void Player::end_turn() {
	// activate trigger effect
	for (auto &active_playing : playing_cards) {
		active_playing->get_ability()->end_turn_trigger(*this);
	}
	if (playing_ritual) {
		playing_ritual->get_ability()->end_turn_trigger(*this);
	}
	// reset all minions' action limit.
	for (auto &c : playing_cards) {
		c->reset_action();
	}
}

// the player receives attack
void Player::receiveattack(int i) {
	health = health - i < 0 ? 0 : health - i;
}


void Player::consumes_magic(int i) {
	if (magic < i) {
		if (test_mode) {
			magic = 0;
		}
		else {
			throw "Insufficient magic";
		}
	}
	else {
		magic = magic - i;
	}
}

int Player::num_playing() {
	return playing_cards.size();
}

int Player::get_health() {
	return health;
}

int Player::get_magic() {
	return magic;
}

// set the minion c on the field
void Player::set_play(shared_ptr<Minion> c, bool need_magic) {
	if (num_playing() >= 5) {
		throw "Maximum playing cards reached!";
	}
	else {
		try {
			if (need_magic) {
				consumes_magic(c->get_cost()); // could throw errormsg.
			}
			playing_cards.emplace_back(c);
			int pos = num_playing() - 1;
			c->set_pos(pos);

			// activate "when a minion enters play" trigger ability.
			for (auto &active_playing : playing_cards) {
				active_playing->get_ability()->enter_play_trigger(*this, *this, c);
			}
			if (playing_ritual) {
				playing_ritual->get_ability()->enter_play_trigger(*this, *this, c);
			}
			for (auto &non_active_playing : opponent->playing_cards) {
				non_active_playing->get_ability()->enter_play_trigger(*this, *opponent, c);
			}
			if (opponent->playing_ritual) {
				opponent->playing_ritual->get_ability()->enter_play_trigger(*this, *opponent, c);
			}
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
}

// set the ritual c on the field
void Player::set_ritual(shared_ptr<Ritual> c) {
	try {
		consumes_magic(c->get_cost()); // could throw errormsg.
		playing_ritual = c;
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}

// send the minion to the grave
void Player::send_grave(shared_ptr<Minion> c) {
	graveyard.emplace_back(c);
}

// remove the card playing at pos, reposition all the other playing cards.
void Player::remove_play(int pos) {
	playing_cards.erase(playing_cards.begin() + pos);
	int new_pos = 0;
	// reposition the remaining playing cards
	for (auto &playing : playing_cards) {
		playing->set_pos(new_pos);
		++new_pos;
	}
}

// replace the playing card at pos, mainly use for adding/removing enchantment to/from a minion.
void Player::replace_play(int pos, shared_ptr<Attackable> nc) {
	playing_cards.erase(playing_cards.begin() + pos);
	playing_cards.insert(playing_cards.begin() + pos, nc);
}

// remove the playing ritual
void Player::remove_ritual() {
	playing_ritual = nullptr;
}

// check if the player is dead (i.e. defeated)
bool Player::isDead() {
	return health <= 0;
}

// send dead minion(s) to graveyard if there is any.
void Player::check_dead_minion() {
	for (int i = 0; i < num_playing();) {
		auto playing = playing_cards[i];
		if (playing->isDead()) {
			cout << name << "'s " << playing->get_minion()->get_name() << 
				" is defeated and is sent to graveyard." << endl;
			remove_play(playing->get_pos());
			shared_ptr<Minion> dead = playing->get_minion();
			playing->reset_state(true);
			send_grave(dead);
		}
		else {
			++i;
		}
	}
}

// attack minion if successful, otherwise throws an error message.
void Player::attack_minion(int i, int j) {
	if (i >= 0 && j >= 0 && i < num_playing() && j < opponent->num_playing()) {
		try {
			shared_ptr<Attackable> who_attack = playing_cards[i];
			shared_ptr<Attackable> target = (opponent->playing_cards)[j];
			who_attack->attack(target); // can throw errormsg	
			cout << who_attack->get_minion()->get_name() << " attacked " <<
				 target->get_minion()->get_name() << "!" << endl;
			check_dead_minion();
			opponent->check_dead_minion();
			
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Attack command failed.";
	}
}

// attack player if successful, otherwise throws an error message.
void Player::attack_player(int i) {
	if (i >= 0 && i < num_playing()) {
		try {
			shared_ptr<Attackable> who_attack = playing_cards[i];
			who_attack->attack(*opponent); // can throw errormsg
			cout << who_attack->get_minion()->get_name() << 
				" attacked " << opponent->name << "!" << endl;

			// attack_player_trigger
			for (auto &active_playing : playing_cards) {
				active_playing->get_ability()->
					attack_player_trigger(who_attack->get_minion(), *opponent);
			}
			if (playing_ritual) {
				playing_ritual->get_ability()->
					attack_player_trigger(who_attack->get_minion(), *opponent);
			}
			for (auto &non_active_playing : opponent->playing_cards) {
				non_active_playing->get_ability()->
					attack_player_trigger(who_attack->get_minion(), *opponent);
			}
			if (opponent->playing_ritual) {
				cout << "accessed" << endl;
				opponent->playing_ritual->get_ability()->
					attack_player_trigger(who_attack->get_minion(), *opponent);

			}
			
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}	
	else {
		throw "Attack command failed.";
	}
}

// play card i if successful, otherwise throws an error message.
void Player::play(int i) {
	if (i >= 0 && i < h->size()) {
		auto card_playing = h->play_card(i);
		try {
			card_playing->play(*this); // could throw errormsg.
			h->remove_card(i);
			cout << name << " played " << card_playing->get_name() << "!" << endl;
			check_dead_minion();
			opponent->check_dead_minion();
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Play command failed.";
	}
}



static const string Need_play_first = "Ability of a minion cannot be played from hand.";

void Player::play_on_minion(int i, Player &p, int j) {
	if (i >= 0 && j >= 0 && i < h->size() && j < p.num_playing()) {
		auto card_playing = h->play_card(i);
		if (dynamic_pointer_cast<Minion>(card_playing)) {
			throw Need_play_first;
		}
		shared_ptr<Attackable> target = (p.playing_cards)[j];
		try {
			(card_playing->get_ability())->activate(*this, p, target,
				card_playing->get_cost());  // could throw errormsg.
			h->remove_card(i);
			cout << name << " played " << card_playing->get_name() << " on " << p.name;
			cout << "'s " << target->get_minion()->get_name() << "!" << endl;

			check_dead_minion();
			opponent->check_dead_minion();


		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Play command failed.";
	}
}
		
void Player::play_on_ritual(int i, Player &p) {
	shared_ptr<Ritual> target = p.playing_ritual;
	if (i >= 0 && i < h->size() && target) {
		auto card_playing = h->play_card(i);
		if (dynamic_pointer_cast<Minion>(card_playing)) {
			throw Need_play_first;
		}
		try {
			(card_playing->get_ability())->activate(*this, p, target,
				card_playing->get_cost()); // could throw errormsg.
			h->remove_card(i);
			cout << name << " played " << card_playing->get_name() << " on " << p.name;
			cout << "'s " << target->get_name() << "!" << endl;
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Play command failed.";
	}
}

// use ability of card i on the field if successful, otherwise throws an error message.
void Player::use(int i) {
	if (i >= 0 && i < num_playing()) {
		shared_ptr<Attackable> card_activating = playing_cards[i];
		if (card_activating->exhausted()) {
			throw "Already attacked, cannot activate ability.";
		}
		try {
			(card_activating->get_minion()->get_ability())->
				activate(*this, card_activating->get_minion()
					->get_active_cost()); // could throw errormsg.
			cout << name << " activated the ability of " << 
				card_activating->get_minion()->get_name() << "!" << endl;
			card_activating->modifyaction();
			check_dead_minion();
			opponent->check_dead_minion();
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Use command failed.";
	}
}

void Player::use_on_minion(int i, Player &p, int j) {
	if (i >= 0 && i < num_playing() && j >= 0 && j < p.num_playing()) {
		shared_ptr<Attackable> card_activating = playing_cards[i];
		shared_ptr<Attackable> target = p.playing_cards[j];
		if (card_activating->exhausted()) {
			throw "Already attacked, cannot activate ability.";
		}
		try {
			(card_activating->get_minion()->get_ability())->
				activate(*this, p, target, card_activating->get_minion()
					->get_active_cost()); // could throw errormsg.
			cout << name << " activated the ability of " << 
				card_activating->get_minion()->get_name() << " on " << p.name;
			cout << "'s " << target->get_minion()->get_name() << "!" << endl;
			card_activating->modifyaction();
			check_dead_minion();
			opponent->check_dead_minion();
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Use command failed.";
	}
}

void Player::use_on_ritual(int i, Player &p) {
	shared_ptr<Ritual> target = p.playing_ritual;
	if (i >= 0 && i < num_playing() && target) {
		shared_ptr<Attackable> card_activating = playing_cards[i];
		if (card_activating->exhausted()) {
			throw "Already attacked, cannot activate ability.";
		}
		try {
			(card_activating->get_minion()->get_ability())->
				activate(*this, p, target, card_activating->get_minion()
					->get_active_cost()); // could throw errormsg.
			cout << name << " activated the ability of " << 
				card_activating->get_minion()->get_name() << " on " << p.name;
			cout << "'s " << target->get_name() << "!" << endl;
			card_activating->modifyaction();
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
	else {
		throw "Use command failed.";
	}
}

string Player::get_name() {
	return name;
}

Player *Player::get_opponent() {
	return opponent;
}

Hand &Player::get_hand () {
	return *h;
}

Deck &Player::get_deck () {
	return *d;
}

vector<shared_ptr<Minion>> &Player::get_grave() {
	return graveyard;
}

vector<shared_ptr<Attackable>> &Player::get_playing() {
	return playing_cards;
}

shared_ptr<Ritual> Player::get_ritual() {
	return playing_ritual;
}

// TESTING MODE FEATURES
void Player::discard(int i) {
	if (test_mode && i < h->size() && i >= 0) {
		h->get_holding().erase(h->get_holding().begin() + i);
	}
	else {
		throw "Testing mode is not enabled or index is invalid";
	}
}

void Player::draw_a_card() {
	if (h->isFull()) {
		throw "No card is drawn because the hand is already fulled";
	}
	else {
		try {
			auto card_drawn = d->draw(); // could throw errormsg.
			h->add_card(card_drawn); 
			cout << "A " << card_drawn->get_name() << " was drawn!" << endl;
		}
		catch (DeckisEmpty &e) {
			throw "No card is drawn because the deck is empty";
		}
	}
}

void Player::draw() {
	if (!test_mode) {
		throw "Testing mode is not enabled";
	}
	else {
		try {
			draw_a_card();
		}
		catch (char const *&ErrorMsg) {
			throw ErrorMsg;
		}
	}
}

