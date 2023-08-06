#include "decorator.h"
#include <memory>
#include "attackable.h"

using namespace std;

Decorator::Decorator(std::string name, int cost, std::shared_ptr<Effect> ability, 
			shared_ptr<Attackable> component) :
	Attackable{name, cost, ability}, component{component} {}

shared_ptr<Attackable> Decorator::get_component() {
	return component;
}
