#include "enchantment.h"
#include <memory>
#include "minion.h"
#include <string>
#include "effect.h"

using namespace std;
//constructor
Enchantment::Enchantment(string name, int cost, shared_ptr<Effect> ability, int atk_boost, int def_boost) :
	Decorator{name, cost, ability, nullptr}, atk_boost{atk_boost}, def_boost{def_boost} {}


void Enchantment::attach(shared_ptr<Attackable> component) {
	this->component = component;
	set_pos(component->get_pos());
}

void Enchantment::play(Player &whoplayed) {
	throw "An enchantment requires a target to play";
}

// attack minion
void Enchantment::attack(shared_ptr<Attackable> target) {
	component->attack(target);
}

// attack player
void Enchantment::attack(Player &other) {
	component->attack(other);
}

// receive an attack
void Enchantment::receiveattack(int i) {
	component->receiveattack(i);
}

// check if dead
bool Enchantment::isDead() {
	return component->isDead();
}

// check if attacked
bool Enchantment::exhausted() {
	return component->exhausted();
}

// modify the action
void Enchantment::modifyaction() {
	component->modifyaction();
}

// reset the action limit of the card (upon ending a turn)
void Enchantment::reset_action() {
	component->reset_action();
}

// remove the enchantment of the minion (upon leaving the field)
void Enchantment::reset_state(bool dead) {
	auto backup = component;
	component = nullptr;
	backup->reset_state(dead);
}

shared_ptr<Minion> Enchantment::get_minion() {
	return component->get_minion();
}

void Enchantment::modify(shared_ptr<Minion> m) {
	component->modify(m);
	get_ability()->enchant(m);
}

shared_ptr<Attackable> Enchantment::get_component() {
	return component;
}
