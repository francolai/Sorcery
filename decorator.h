#ifndef decorator_h
#define decorator_h
#include "attackable.h"
#include <memory>

class Decorator : public Attackable {
	protected:
	std::shared_ptr<Attackable> component;
	public:
	Decorator(std::string name, int cost, std::shared_ptr<Effect> ability, 
			std::shared_ptr<Attackable> component);
	std::shared_ptr<Attackable> get_component();
};

#endif
