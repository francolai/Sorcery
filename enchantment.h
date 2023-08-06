#ifndef enchantment_h
#define enchantment_h
#include "decorator.h"
#include <memory>
#include <string>

class Attackable;
class Minion;

class Enchantment : public Decorator {
	int atk_boost; // 0 if no stat boost
	int def_boost;
	public:
	Enchantment(std::string name, int cost, std::shared_ptr<Effect> ability,
		 int atk_boost = 0, int def_boost = 0);

	void attach(std::shared_ptr<Attackable> component);
	void play(Player &whoplayed) override;
	void attack(std::shared_ptr<Attackable> target) override;
	void attack(Player &other) override;
	void receiveattack(int i) override;
	void modifyaction() override;
	bool exhausted() override;
	bool isDead() override;
	void reset_action() override;
	std::shared_ptr<Minion> get_minion() override;
	void reset_state(bool dead = false) override;
	void modify(std::shared_ptr<Minion> m) override;
	std::shared_ptr<Attackable> get_component() override;
};
	

#endif
