#ifndef player_h
#define player_h
#include <vector>
#include <memory>
#include "deck.h"
#include "hand.h"
//#include "subject.h"

class Card;
class Attackable;
class Minion;
class Ritual;
class TriggerEffect;
class Effect;

const int init_health = 20;
const int init_magic = 3;

class Player {
	std::string name;
	int health;
	int magic;
	Player *opponent;
	bool test_mode;
	std::unique_ptr<Deck> d;
	std::unique_ptr<Hand> h;
	std::vector<std::shared_ptr<Minion>> graveyard;
	std::vector<std::shared_ptr<Attackable>> playing_cards;
	std::shared_ptr<Ritual> playing_ritual;
	std::unique_ptr<Deck> load_deck(std::string filename);

	public:
	void init(std::string name, std::string filename, bool test_mode, Player *opponent);
	void start_turn();
	void end_turn();
	void receiveattack(int i);
	void consumes_magic(int i);
	bool isDead();
	void set_play(std::shared_ptr<Minion> c, bool need_magic);
	void set_ritual(std::shared_ptr<Ritual> c);
	void send_grave(std::shared_ptr<Minion> c);
	void remove_play(int pos);
	void remove_ritual();
	void replace_play(int pos, std::shared_ptr<Attackable> nc);
	void check_dead_minion();

	void attack_minion(int i, int j); // using card i owned by curr player to attack card j of the other
	void attack_player(int i); // attack the other player

	// play minion, ritual, or spells with no target
	void play(int i); // play the card i from hand
	// play enchantment, or spells with a target
	void play_on_minion(int i, Player &p, int j); // play the card i from hand on card j of player 
	void play_on_ritual(int i, Player &p); // play the card i from hand on the ritual of player p

	void use(int i); //use the ability (no target) of card i, pass the 
					//information of the two players to use the method of Card.
	void use_on_minion(int i, Player &p, int j);
	void use_on_ritual(int i, Player &p);

	int num_playing(); // number of cards playing
	std::string get_name();
	int get_health();
	int get_magic();
	Player *get_opponent();
	Hand &get_hand();
	Deck &get_deck();
	std::vector<std::shared_ptr<Minion>>& get_grave();
	std::vector<std::shared_ptr<Attackable>>& get_playing();
	std::shared_ptr<Ritual> get_ritual();
	void draw_a_card();

	// TESTING MODE FEATURES
	void discard(int i);
	void draw();
};

#endif
