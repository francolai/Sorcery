#include "textdisplay.h"
#include "ritual.h"
#include "spell.h"
#include "minion.h"
#include "enchantment.h"	
#include <iostream>
#include "ascii_graphics.h"

using namespace std;

static void displayplaying(Player &p);

void displayboard(Player &p1, Player &p2) {
	//CARD_TEMPLATE_EMPTY;
	//CARD_TEMPLATE_BORDER;
	string tmp;
	string desc;
	card_template_t r1;
	card_template_t r2;
	int activation_cost;
	// print top boundary
	cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
	for (int num = 0; num < 165; ++num) {
		cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
	// 1st line
	// ritual
	r1 = CARD_TEMPLATE_BORDER;
	if (p1.get_ritual()) {
		tmp = p1.get_ritual()->get_name();
	
	if (tmp == "Dark Ritual") {
		desc = "At the start of your turn, gain 1 mana";
		activation_cost = 1;
	}
	else if (tmp == "Aura of Power") {
		desc = "Whenever a minion enters play under your control, it gains +1/+1";
		activation_cost = 1;
	}
	else if (tmp == "Standstill") {
		desc = "Whenever a minion enters play, destroy it";
		activation_cost = 2;
	}
	else if (tmp == "Shield") { // ----------------------------------------------------------custom virtual
		desc = "When a minion attack your minion, stop the attack";
		activation_cost = 2;
	}
	else {} 

	r1 = display_ritual(tmp,p1.get_ritual()->get_cost(), activation_cost, desc, 
		p1.get_ritual()->get_charge());
	}
	//p1
	card_template_t player1 = display_player_card(1,p1.get_name(), p1.get_health(), p1.get_magic());
	// print top yard(only contain minion) for p1
	
	card_template_t y1 = CARD_TEMPLATE_BORDER;
	if (p1.get_grave().size() != 0) {
		tmp = (p1.get_grave().back())->get_name();
	if (tmp == "Air Elemental") {
		y1 = display_minion_no_ability(tmp,0,1,1);
	}
	else if (tmp == "Earth Elemental") {
		y1 = display_minion_no_ability(tmp,3,4,4);
	}
	else if (tmp == "Fire Elemental") {
		desc = "Whenever an opponent's minion enters play, deal 1 damage to it.";
		y1 = display_minion_triggered_ability(tmp,2,2,2,desc);
	}
	else if (tmp == "Potion Seller") {
		desc = "At the end of your turn, all your minions gain +0/+1.";
		y1 = display_minion_triggered_ability(tmp,2,1,3,desc);
	}
	else if (tmp == "Novice Pyromancer") {
		desc = "Deal 1 damage to target minion";
		y1 = display_minion_activated_ability(tmp,1,0,1,1,desc);
	}
	else if (tmp == "Apprentice Summoner") {
		desc = "Summon a 1/1 air elemental";
		y1 = display_minion_activated_ability(tmp,1,1,1,1,desc);
	}
	else if (tmp == "Master Summoner") {
		desc = "Summon up to three 1/1 air elementals";
		y1 = display_minion_activated_ability(tmp,3,2,3,2,desc);
	}
	else if (tmp == "Little Hero") { // ----------------------------------------------------------custom minion
		desc = "Damage enemy 5 lives.";
		y1 = display_minion_activated_ability(tmp,1,0,5,3,desc);
	}
	else {}
	}
	for (int i = 0; i < 11; ++i) {
			cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
			cout << r1[i] << CARD_TEMPLATE_EMPTY[i] << player1[i] << CARD_TEMPLATE_EMPTY[i] << y1[i];
			cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
	}
	// 2nd line
	//print minions on the board for p1
	displayplaying(p1);
	// 3rd line
	// print center_graph -> SORCERY
	for (int i = 0; i < static_cast<int>(CENTRE_GRAPHIC.size()); ++i) {
		cout << CENTRE_GRAPHIC[i] << endl;
	}
	// 4th line
	// print minions on the board for p2
	displayplaying(p2);
	// 5th line
	// ritual
	r2 = CARD_TEMPLATE_BORDER;
	if (p2.get_ritual()) {
		tmp = p2.get_ritual()->get_name();
	
	if (tmp == "Dark Ritual") {
		desc = "At the start of your turn, gain 1 mana";
		activation_cost = 1;
	}
	else if (tmp == "Aura of Power") {
		desc = "Whenever a minion enters play under your control, it gains +1/+1";
		activation_cost = 1;
	}
	else if (tmp == "Standstill") {
		desc = "Whenever a minion enters play, destroy it";
		activation_cost = 2;
	}
	else if (tmp == "Shield") { // ----------------------------------------------------------custom virtual
		desc = "When a minion attack your minion, stop the attack";
		activation_cost = 2;
	}
	else {} 

	r2 = display_ritual(tmp,p2.get_ritual()->get_cost(), activation_cost, desc, 
		p2.get_ritual()->get_charge());
	}
	//p1
	card_template_t player2 = display_player_card(1,p2.get_name(), p2.get_health(), p2.get_magic());
	// print top yard(only contain minion) for p2
	card_template_t y2 = CARD_TEMPLATE_BORDER;
	if (p2.get_grave().size() != 0) {
		tmp = (p2.get_grave().back())->get_name();
	if (tmp == "Air Elemental") {
		y2 = display_minion_no_ability(tmp,0,1,1);
	}
	else if (tmp == "Earth Elemental") {
		y2 = display_minion_no_ability(tmp,3,4,4);
	}
	else if (tmp == "Fire Elemental") {
		desc = "Whenever an opponent's minion enters play, deal 1 damage to it.";
		y2 = display_minion_triggered_ability(tmp,2,2,2,desc);
	}
	else if (tmp == "Potion Seller") {
		desc = "At the end of your turn, all your minions gain +0/+1.";
		y2 = display_minion_triggered_ability(tmp,2,1,3,desc);
	}
	else if (tmp == "Novice Pyromancer") {
		desc = "Deal 1 damage to target minion";
		y2 = display_minion_activated_ability(tmp,1,0,1,1,desc);
	}
	else if (tmp == "Apprentice Summoner") {
		desc = "Summon a 1/1 air elemental";
		y2 = display_minion_activated_ability(tmp,1,1,1,1,desc);
	}
	else if (tmp == "Master Summoner") {
		desc = "Summon up to three 1/1 air elementals";
		y2 = display_minion_activated_ability(tmp,3,2,3,2,desc);
	}
	else if (tmp == "Little Hero") { // ----------------------------------------------------------custom minion
		desc = "Damage enemy 5 lives.";
		y2 = display_minion_activated_ability(tmp,1,0,5,3,desc);
	}
	else {} // custom card
	}
	for (int i = 0; i < 11; ++i) {
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
		cout << r2[i] << CARD_TEMPLATE_EMPTY[i] << player2[i] << CARD_TEMPLATE_EMPTY[i] << y2[i];
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
	}
	// print bottom boundary
	cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
	for (int num = 0; num < 165; ++num) {
		cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

static void displayplaying(Player &p) {
	vector<card_template_t> b;
	card_template_t b1 = CARD_TEMPLATE_BORDER;
	card_template_t b2 = CARD_TEMPLATE_BORDER;
	card_template_t b3 = CARD_TEMPLATE_BORDER;
	card_template_t b4 = CARD_TEMPLATE_BORDER;
	card_template_t b5 = CARD_TEMPLATE_BORDER;
	b.push_back(b1);
	b.push_back(b2);
	b.push_back(b3);
	b.push_back(b4);
	b.push_back(b5);
	for (int i = 0; i < p.num_playing(); ++i) {
	string tmp = (p.get_playing())[i]->get_minion()->get_name();
	int c = (p.get_playing())[i]->get_minion()->get_cost();
	int a = (p.get_playing())[i]->get_minion()->get_atk();
	int d = (p.get_playing())[i]->get_minion()->get_defence();
	int cc = (p.get_playing())[i]->get_minion()->get_active_cost();
	string desc;
	if (tmp == "Air Elemental") {
		b[i] = display_minion_no_ability(tmp,c,a,d);
	}
	else if (tmp == "Earth Elemental") {
		b[i] = display_minion_no_ability(tmp,c,a,d);
	}
	else if (tmp == "Fire Elemental") {
		desc = "Whenever an opponent's minion enters play, deal 1 damage to it.";
		b[i] = display_minion_triggered_ability(tmp,c,a,d,desc);
	}
	else if (tmp == "Potion Seller") {
		desc = "At the end of your turn, all your minions gain +0/+1.";
		b[i] = display_minion_triggered_ability(tmp,c,a,d,desc);
	}
	else if (tmp == "Novice Pyromancer") {
		desc = "Deal 1 damage to target minion";
		b[i] = display_minion_activated_ability(tmp,c,a,d,cc,desc);
	}
	else if (tmp == "Apprentice Summoner") {
		desc = "Summon a 1/1 air elemental";
		b[i] = display_minion_activated_ability(tmp,c,a,d,cc,desc);
	}
	else if (tmp == "Master Summoner") {
		desc = "Summon up to three 1/1 air elementals";
		b[i] = display_minion_activated_ability(tmp,c,a,d,cc,desc);
	}
	else if (tmp == "Little Hero") { // ----------------------------------------------------------custom minion
		desc = "Damage enemy 5 lives.";
		b[i] = display_minion_activated_ability(tmp,c,a,d,cc,desc);
	}
	else {} // custom card
	}
	for (int i = 0; i < 11; ++i) {
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
		cout << b[0][i] << b[1][i] << b[2][i] << b[3][i] << b[4][i];
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
	}
}


void displayhand(Player &p) {
	vector<card_template_t> hand;
	card_template_t h1 = CARD_TEMPLATE_BORDER;
	card_template_t h2 = CARD_TEMPLATE_BORDER;
	card_template_t h3 = CARD_TEMPLATE_BORDER;
	card_template_t h4 = CARD_TEMPLATE_BORDER;
	card_template_t h5 = CARD_TEMPLATE_BORDER;
	hand.push_back(h1);
	hand.push_back(h2);
	hand.push_back(h3);
	hand.push_back(h4);
	hand.push_back(h5);
	string tmp; 
	string desc;
	for (int i = 0; i < p.get_hand().size(); ++i) {
		tmp = (p.get_hand().get_holding())[i]->get_name();
		if (tmp == "Air Elemental") {
			hand[i] = display_minion_no_ability(tmp,0,1,1);
		}
		else if (tmp == "Earth Elemental") {
			hand[i] = display_minion_no_ability(tmp,3,4,4);
		}
		else if (tmp == "Fire Elemental") {
			desc = "Whenever an opponent's minion enters play, deal 1 damage to it.";
			hand[i] = display_minion_triggered_ability(tmp,2,2,2,desc);
		}
		else if (tmp == "Potion Seller") {
			desc = "At the end of your turn, all your minions gain +0/+1.";
			hand[i] = display_minion_triggered_ability(tmp,2,1,3,desc);
		}
		else if (tmp == "Novice Pyromancer") {
			desc = "Deal 1 damage to target minion";
			hand[i] = display_minion_activated_ability(tmp,1,0,1,1,desc);
		}
		else if (tmp == "Apprentice Summoner") {
			desc = "Summon a 1/1 air elemental";
			hand[i] = display_minion_activated_ability(tmp,1,1,1,1,desc);
		}
		else if (tmp == "Master Summoner") {
			desc = "Summon up to three 1/1 air elementals";
			hand[i] = display_minion_activated_ability(tmp,3,2,3,2,desc);
		}
		else if (tmp == "Little Hero") { // ----------------------------------------------------------custom minion
			desc = "Damage enemy 5 lives.";
			hand[i] = display_minion_activated_ability(tmp,1,0,5,5,desc);
		}
		else if (tmp == "Banish") {
			desc = "Destroy target minion or ritual";
			hand[i] = display_spell(tmp,2,desc);
		}
		else if (tmp == "Unsummon") {
			desc = "Return target minion to its owner's hand";
			hand[i] = display_spell(tmp,1,desc);
		}
		else if (tmp == "Recharge") {
			desc = "Your ritual gains 3 charges";
			hand[i] = display_spell(tmp,1,desc);
		}
		else if (tmp == "Disenchant") {
			desc = "Destroy the top enchantment on target minion";
			hand[i] = display_spell(tmp,1,desc);
		}
		else if (tmp == "Raise Dead") {
			desc = "Resurrect the top minion in your graveyard";
			hand[i] = display_spell(tmp,1,desc);
		}
		else if (tmp == "Blizzard") {
			desc = "Deal 2 damage to all minions";
			hand[i] = display_spell(tmp,3,desc);
		}
		else if (tmp == "Gift") {// ----------------------------------------------------------custom spell
			desc = "Increase 3 magic to the player";
			hand[i] = display_spell(tmp,0,desc);
		}
		else if (tmp == "Giant Strength") {
			hand[i] = display_enchantment_attack_defence(tmp,1,"","+2","+2");
		}
		else if (tmp == "Magic Fatigue") {
			desc = "Enchanted minion's activated ability costs 2 more";
			hand[i] = display_enchantment(tmp,0,desc);
		}
		else if (tmp == "Silence") {
			desc = "Enchanted minion cannot use abilities";
			hand[i] = display_enchantment(tmp,0,desc);
		}
		else if (tmp == "Extra Draw") {// ----------------------------------------------------------custom enchantment
			desc = "Grant the enchanted minion an activated ability to draw a new card. When activated, consumes 1 magic";
			hand[i] = display_enchantment(tmp,1,desc);
		}
		else if (tmp == "Dark Ritual") {
			desc = "At the start of your turn, gain 1 mana";
			hand[i] = display_ritual(tmp,0,1,desc,5);
		}
		else if (tmp == "Aura of Power") {
			desc = "Whenever a minion enters play under your control, it gains +1/+1";
			hand[i] = display_ritual(tmp,1,1,desc,4);
		}
		else if (tmp == "Standstill") {
			desc = "Whenever a minion enters play, destroy it";
			hand[i] = display_ritual(tmp,3,2,desc,4);
		}
		else if (tmp == "Shield") {// ----------------------------------------------------------custom ritual
			desc = "When the player receive an attack, stop the attack";
			hand[i] = display_ritual(tmp,0,2,desc,2);
		}
		else {} // custom card
	}
	for (int i = 0; i < 11; ++i) {
			cout << hand[0][i] << hand[1][i] << hand[2][i] << hand[3][i] << hand[4][i] << endl;
	}
}

void inspect(Player &p, int i) {
	vector<string> v;
	if (p.get_playing().size() == 0) {
		throw "There is no cards on the board";
	}
	int atk = p.get_playing()[i]->get_minion()->get_atk();
	int defence = p.get_playing()[i]->get_minion()->get_defence();
	int cost = p.get_playing()[i]->get_minion()->get_active_cost();
	string m = p.get_playing()[i]->get_minion()->get_name();
	auto tmp = p.get_playing()[i];
	while (tmp->get_name() != m) {
		v.push_back(tmp->get_name());
		tmp = tmp->get_component();
	}
	//Display
	string desc;
	//int counter = 0;
	// Display minion
	card_template_t mini;
	if (m == "Air Elemental") {
		mini = display_minion_no_ability(m,0, atk,defence);
	}
	else if (m == "Earth Elemental") {
		mini = display_minion_no_ability(m,3, atk,defence);
	}
	else if (m == "Fire Elemental") {
		desc = "Whenever an opponent's minion enters play, deal 1 damage to it.";
		mini = display_minion_triggered_ability(m,2,atk,defence,desc);
	}
	else if (m == "Potion Seller") {
		desc = "At the end of your turn, all your minions gain +0/+1.";
		mini = display_minion_triggered_ability(m,2,atk,defence,desc);
	}
	else if (m == "Novice Pyromancer") {
		desc = "Deal 1 damage to target minion";
		mini = display_minion_activated_ability(m,1, atk,defence,cost,desc);
	}
	else if (m == "Apprentice Summoner") {
		desc = "Summon a 1/1 air elemental";
		mini = display_minion_activated_ability(m,1,atk,defence,cost,desc);
	}
	else if (m == "Master Summoner") {
		desc = "Summon up to three 1/1 air elementals";
		mini = display_minion_activated_ability(m,3,atk,defence,cost,desc);
	}
	else if (m == "Little Hero") { // ----------------------------------------------------------custom minion
		desc = "Damage enemy 5 lives.";
		mini = display_minion_activated_ability(m,1,atk,defence,cost,desc);
	}
	else {} 

	vector <card_template_t> e;
	card_template_t empty = CARD_TEMPLATE_BORDER;
	for (int n = 0; n < static_cast<int>(v.size()); ++n) {
		if (v[n] == "Giant Strength") {
			e.insert(e.begin(), display_enchantment_attack_defence("Giant Strength",1,"","+2","+2"));
		}
		else if (v[n] == "Magic Fatigue") {
			desc = "Enchanted minion's activated ability costs 2 more";
			e.insert(e.begin(), display_enchantment("Magic Fatigue",0,desc));
		}
		else if (v[n] == "Silence") {
			desc = "Enchanted minion cannot use abilities";
			e.insert(e.begin(), display_enchantment("Silence",0,desc));
		}
		else if (v[n] == "Extra Draw") {// ----------------------------------------------------------custom enchantment
			desc = "Grant the enchanted minion an activated ability to draw a new card. When activated, consumes 1 magic";
			e.insert(e.begin(), display_enchantment("Extra Draw",1,desc));
		}
	else {} 
	}	
	// print
	int d = e.size()/5;
	int r = d*5;
	for (int n = 0; n < 11; ++n) {
		cout << mini[n] << endl;
	}


	//for (int n = 0; n < static_cast<int>(v.size()); ++n) {
	//	cout << v[n] << endl;
	//}


	if (e.size() < 5 && e.size() != 0) {
		for (int n = 0; n < 11; ++n) {
			for (int g = 0; g < static_cast<int>(e.size()); ++g) {
				cout << e[g][n];
			}
			cout << endl;
		}
	}

	if (e.size() >= 5 && e.size() != 0) {
		for (int m = 0; m < 5*d; m+=5) {
			for (int n = 0; n < 11; ++n) {
				for (int g = m; g < m+5; ++g) {
					cout << e[g][n];
				}
				cout << endl;
			}
		}
	}

	if (e.size() > 5 && (e.size() != 0)) {
		for (int n = 0; n < 11; ++n) {
			for (int g = r; g < static_cast<int>(e.size()); ++g) {
				cout << e[g][n];
			}
			cout << endl;
		}
	}
}

