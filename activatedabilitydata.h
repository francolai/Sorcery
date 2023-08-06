#ifndef activatedabilitydata_h
#define activatedabilitydata_h
#include "activatedeffect.h"
#include <memory>

class Player;
class Attackable;
class Ritual;

class NoAbility : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target,
			int cost) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Ritual> target,
			int cost) override;
};

class NovicePyromancerE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target,
			int cost) override;
};

class ApprenticeSummonerE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

class LittleHeroE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

class MasterSummonerE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

class BanishE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target,
			int cost) override;
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Ritual> target,
			int cost) override;
};

class UnsummonE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target,
			int cost) override;
};

class RechargeE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost);
};

class DisenchantE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, Player &targetP, std::shared_ptr<Attackable> target,
			int cost) override;
};

class RaiseDeadE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

class BlizzardE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

class DrawACard : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

class GiftE : public ActivatedEffect {
	public:
	void activate(Player &whoactivated, int cost) override;
};

#endif

