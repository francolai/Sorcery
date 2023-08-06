#ifndef enchantmentabilitydata_h
#define enchantmentabilitydata_h
#include "enchantmenteffect.h"
#include <memory>

class Minion;
class Attackable;
class Player;

class GiantStrengthE : public EnchantmentEffect {
	public:
	void enchant(std::shared_ptr<Minion> m) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target, int cost) override;
};

class MagicFatigueE : public EnchantmentEffect {
	public:
	void enchant(std::shared_ptr<Minion> m) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target, int cost) override;
};

class SilenceE : public EnchantmentEffect {
	public:
	void enchant(std::shared_ptr<Minion> m) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target, int cost) override;
};

class ExtraDrawE : public EnchantmentEffect {
	public:
	void enchant(std::shared_ptr<Minion> m) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target, int cost) override;
};

#endif

