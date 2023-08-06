#include "carddata.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
#include "activatedabilitydata.h"
#include "triggerabilitydata.h"
#include "enchantmentabilitydata.h"
#include <memory>
#include <iostream>


using namespace std;

// return the card given its name, add more if needed.
std::shared_ptr<Card> construct_card(std::string name) {
	// MINION SECTION
	if (name == "Air Elemental") {
		return make_shared<Minion>
			("Air Elemental", 0, std::make_shared<NoAbility>(), 1, 1);
	}
	else if (name == "Earth Elemental") {
		return make_shared<Minion>
			("Earth Elemental",  3, std::make_shared<NoAbility>(), 4, 4);
	}
	else if (name == "Fire Elemental") {
		return make_shared<Minion>
			("Fire Elemental", 2, std::make_shared<FireElementalE>(), 2, 2);
	}
	else if (name == "Potion Seller") {
		return make_shared<Minion>
			("Potion Seller", 2, std::make_shared<PotionSellerE>(), 1, 3);
	}
	else if (name == "Novice Pyromancer") {
		return make_shared<Minion>
			("Novice Pyromancer", 1, std::make_shared<NovicePyromancerE>(), 0, 1, 1);
	}
	else if (name == "Apprentice Summoner") {
		return make_shared<Minion>
			("Apprentice Summoner", 1, std::make_shared<ApprenticeSummonerE>(), 1, 1, 1);
	}
	else if (name == "Master Summoner") {
		return make_shared<Minion>
			("Master Summoner", 3, std::make_shared<MasterSummonerE>(), 2, 3, 2);
	}
	else if (name == "Little Hero") {
		return make_shared<Minion>
			("Little Hero", 1, std::make_shared<LittleHeroE>(), 1, 5, 5);
	}

	// SPELL SECTION
	else if (name == "Banish") {
		return make_shared<Spell>
			("Banish", 2, std::make_shared<BanishE>());
	}
	else if (name == "Unsummon") {
		return make_shared<Spell>
			("Unsummon", 1, std::make_shared<UnsummonE>());
	}
	else if (name == "Recharge") {
		return make_shared<Spell>
			("Recharge", 1, std::make_shared<RechargeE>());
	}
	else if (name == "Disenchant") {
		return make_shared<Spell>
			("Disenchant", 1, std::make_shared<DisenchantE>());
	}
	else if (name == "Raise Dead") {
		return make_shared<Spell>
			("Raise Dead", 1, std::make_shared<RaiseDeadE>());
	}
	else if (name == "Blizzard") {
		return make_shared<Spell>
			("Blizzard", 3, std::make_shared<BlizzardE>());
	}
	else if (name == "Gift") {
		return make_shared<Spell>
			("Gift", 0, std::make_shared<GiftE>());
	}


	// ENCHANTMENT SECTION
	else if (name == "Giant Strength") {
		return make_shared<Enchantment>
			("Giant Strength", 1, std::make_shared<GiantStrengthE>(), 2, 2);
	}
	else if (name == "Magic Fatigue") {
		return make_shared<Enchantment>
			("Magic Fatigue", 0, std::make_shared<MagicFatigueE>());
	}
	else if (name == "Silence") {
		return make_shared<Enchantment>
			("Silence", 1, std::make_shared<SilenceE>());
	}
	else if (name == "Extra Draw") {
		return make_shared<Enchantment>
			("Extra Draw", 1, std::make_shared<ExtraDrawE>());
	}

	// RITUAL SECTION
	else if (name == "Dark Ritual") {
		return make_shared<Ritual>
			("Dark Ritual", 0, std::make_shared<DarkRitualE>(), 5);
	}
	else if (name == "Aura of Power") {
		return make_shared<Ritual>
			("Aura of Power", 1, std::make_shared<AuraOfPowerE>(), 4);
	}
	else if (name == "Standstill") {
		return make_shared<Ritual>
			("Standstill", 3, std::make_shared<StandstillE>(), 4);
	}
	else if (name == "Shield") {
		return make_shared<Ritual>
			("Shield", 0, std::make_shared<ShieldE>(), 2);
	}
	
	else {
		throw "Cannot construct card";
	}
	
}


/*
// MINIONS
Minion AirElemental{"Air Elemental", 0, std::make_shared<NoAbility>(), 1, 1};
Minion EarthElemental{"Earth Elemental",  3, std::make_shared<NoAbility>(), 4, 4};
Minion FireElemental{"Fire Elemental", 2, std::make_shared<FireElementalE>(), 2, 2};
Minion PotionSeller{"Potion Seller", 2, std::make_shared<PotionSellerE>(), 1, 3};
Minion NovicePyromancer{"Novice Pyromancer", 1, std::make_shared<NovicePyromancerE>(), 0, 1, 1};
Minion ApprenticeSummoner{"Apprentice Summoner", 1, std::make_shared<ApprenticeSummonerE>(), 1, 1, 1};
Minion MasterSummoner{"Master Summoner", 3, std::make_shared<MasterSummonerE>(), 2, 3, 2};
Minion RealHero{"Real Hero", 1, std::make_shared<RealHeroE>(), 1, 5, 3};

// SPELLS
Spell Banish{"Banish", 2, std::make_shared<BanishE>()};
Spell Unsummon{"Unsummon", 1, std::make_shared<UnsummonE>()};
Spell Recharge{"Recharge", 1, std::make_shared<RechargeE>()};
Spell Disenchant{"Disenchant", 1, std::make_shared<DisenchantE>()};
Spell RaiseDead{"Raise Dead", 1, std::make_shared<RaiseDeadE>()};
Spell Blizzard{"Blizzard", 3, std::make_shared<BlizzardE>()};
Spell Gift{"Gift", 0, std::make_shared<GiftE>()};


// ENCHANTMENTS
Enchantment GiantStrength{"Giant Strength", 1, std::make_shared<GiantStrengthE>(), 2, 2};
Enchantment MagicFatigue{"Magic Fatigue", 0, std::make_shared<MagicFatigueE>()};
Enchantment Silence{"Silence", 1, std::make_shared<SilenceE>()};
Enchantment ExtraDraw{"Extra Draw", 1, std::make_shared<ExtraDrawE>()};

// RITUALS
Ritual DarkRitual{"Dark Ritual", 0, std::make_shared<DarkRitualE>(), 5};
Ritual AuraOfPower{"Aura of Power", 1, std::make_shared<AuraOfPowerE>(), 4};
Ritual Standstill{"Standstill", 3, std::make_shared<StandstillE>(), 4};
Ritual Shield{"Shield", 2, std::make_shared<StandstillE>(), 2};
*/

