#ifndef minion_h
#define minion_h
#include "attackable.h"
#include <memory>
#include "player.h"

class Effect;

class Minion : public Attackable, public std::enable_shared_from_this<Minion> {
	int atk;
	int defence;
	bool hasAttacked;
	int active_cost;
	int health_lost;
	const int original_atk;
	const int original_def;
	const std::shared_ptr<Effect> original_ability;
	const int original_ac;
	public:
	Minion(std::string name, int cost, std::shared_ptr<Effect> ability, 
		int atk, int def, int ac = 0);

	void play(Player &whoplayed) override;
	void attack(std::shared_ptr<Attackable> target) override;
	void attack(Player &other) override;
	void receiveattack(int i) override;
	void modifyattack(int i);
	void modifydefence(int i);
	void modifyability(std::shared_ptr<Effect> ability);
	void modify_active_cost(int i);
	void modifyaction() override;
	bool isDead() override;
	bool exhausted() override;
	void reset_action() override;
	void reset_state(bool dead = false) override;
	std::shared_ptr<Minion> get_minion() override;
	void modify(std::shared_ptr<Minion> m) override;

	int get_atk();
	int get_defence();
	int get_active_cost();
};

#endif
