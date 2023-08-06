#include "minion.h"
#include "player.h"
#include <memory>
#include <iostream>

using namespace std;

//constructor
Minion::Minion(string name, int cost, shared_ptr<Effect> ability, int atk, int def, int ac) :
	Attackable{name, cost, ability}, atk{atk}, defence{def}, 
	hasAttacked{false}, active_cost{ac}, health_lost{0}, original_atk{atk}, 
	original_def{def}, original_ability{ability}, original_ac{ac} {}

shared_ptr<Minion> Minion::get_minion() {
	return shared_from_this();
}

// play the card if successful, otherwise throw an error message.
void Minion::play(Player &whoplayed) {
	try {
		whoplayed.set_play(shared_from_this(), true);
	}
	catch (char const *&ErrorMsg) {
		throw ErrorMsg;
	}
}

// attack minion if successful, otherwise an errormsg is thrown
void Minion::attack(shared_ptr<Attackable> target) {
	if (hasAttacked) {
		throw "This minion already attacked in this turn.";
	}
	else {	
		target->receiveattack(atk);
		receiveattack(target->get_minion()->atk);
		hasAttacked = true;

	}
}		

// attack player if successful, otherwise an errormsg is thrown
void Minion::attack(Player &other) {
	if (hasAttacked) {
		throw "This minion already attacked in this turn.";
	}
	else {
		other.receiveattack(this->atk);
		hasAttacked = true;
	}
}

// receive an attack
void Minion::receiveattack(int i) {
	defence = defence - i < 0 ? 0 : defence - i;
	health_lost += i;
}

// modify the attack
void Minion::modifyattack(int i) {
	atk += i;
}

// modify the defence
void Minion::modifydefence(int i) {
	defence += i;
}

// modify the ability
void Minion::modifyability(shared_ptr<Effect> ability) {
	this->ability = ability;
}

// modify the action
void Minion::modifyaction() {
	hasAttacked = true;
}

// check if dead
bool Minion::isDead() {
	return defence <= 0;
}

// check if attacked
bool Minion::exhausted() {
	return hasAttacked;
}

// reset the action limit of the card (upon ending a turn)
void Minion::reset_action() {
	hasAttacked = false;
}

// reset the atk and def of the minion (upon leaving the field)
void Minion::reset_state(bool dead) {
	atk = original_atk;
	defence = original_def;
	ability = original_ability;
	active_cost = original_ac;
	if (!dead) {
		defence = (defence - health_lost < 0) ? 0 : defence - health_lost;
	}
	else {
		health_lost = 0;
		hasAttacked = false;
	}
}

void Minion::modify(shared_ptr<Minion> m) {
	reset_state();
}

void Minion::modify_active_cost(int i) {
	active_cost += i;
}

int Minion::get_atk() {
	return atk;
}

int Minion::get_defence() {
	return defence;
}

int Minion::get_active_cost() {
	return active_cost;
}
