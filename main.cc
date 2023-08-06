#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "player.h"
#include "textdisplay.h"
using namespace std;

int main(int argc, char *argv[]) {
	ifstream init;
	string p1deck = "default.deck";
	string p2deck = "default.deck";
	bool test_mode = false;
	// Handle command line arguments
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg == "-deck1") {
			// load deck from file for player 1
			++i;
			p1deck = argv[i];
		}
		else if (arg == "-deck2") {
			// load deck from file for play 2
			++i;
			p2deck = argv[i];
		}
		else if (arg == "-init") {
			// load game from file
			++i;
			init.open(argv[i]);
		}
		else if (arg == "-testing") {
			// enable testing mode
			test_mode = true;
		}
		else {}
	}
	
	// initialize game
	string p1name, p2name;
	cout << "What is Player 1's name?" << endl;
	if (init >> p1name) {}
	else {
		cin >> p1name;
	}
	cout << "What is Player 2's name?" << endl;
	if (init >> p2name) {}
	else {
		cin >> p2name;
	}
	Player p1;
	Player p2;
		/* do other proper initialization here
		e.g. initialize deck, hand of the players */
	p1.init(p1name, p1deck, test_mode, &p2);
	p2.init(p2name, p2deck, test_mode, &p1);

	// Command interpreter
	string cmdline;
	string sepcmd;
	Player *curr_player = &p1;
	Player *other_player = &p2;
	while (true) {
		istringstream iss;
		if (getline(init, cmdline)) {
			iss.str(cmdline);
		}
		else {
			getline(cin, cmdline);
			iss.str(cmdline);
		}
		if (cin.eof()) {
			break;
		}
		try {
			iss >> sepcmd;
			if (sepcmd == "help") {
				//display help message
				ifstream helpfile{"help.txt"};
				string s;
				while(getline(helpfile, s)) {
					cout << s << endl;
				}				
			}
			else if (sepcmd == "end") {
				// end the current player's turn
				curr_player->end_turn();

				// the next player's turn starts
				Player *tmp = curr_player;
				curr_player = other_player;
				other_player = tmp;
				curr_player->start_turn();
			}
			else if (sepcmd == "quit") {
				// terminate the game
				break;
			}
			else if (sepcmd == "attack") { 
				// attack player or enemy's minion
				// cin minion(s)
				int minion;
				int other_minion;
				// call attack method
				if (iss >> minion) {
					if (iss >> other_minion) {
						curr_player->attack_minion(minion-1,other_minion-1);
					}
					else {
					curr_player->attack_player(minion-1);
					}
				}
				else {
					continue;
				}
			}
			else if (sepcmd == "play") { //play cards on the hand
				// do proper cin stuff here
				int card;
				int player;
				char other_card;
				if (iss	>> card) {
					if (iss >> player) {
						Player *other;
						if (player == 1) {
							other = &p1;
						} 
						else if (player == 2) {
							other = &p2;
						}
						else {
							throw "Invalid Input";
						}
						if (iss >> other_card) {
							if (other_card == 'r') {
								curr_player->play_on_ritual(card-1, *other);
							}
							else {
								int other_card_int = other_card - '0';
								curr_player->play_on_minion(card-1, *other, other_card_int-1);
							}
						}
					} 
					else {
						curr_player->play(card-1);
					}
				}
			}
			else if (sepcmd == "use") { // use ability of a minion currently ON THE FIELD
				// do proper cin stuff here
				int card;
				int player;
				char other_card;
				if (iss	>> card) {
					if (iss >> player) {
						Player *other;
						if (player == 1) {
							other = &p1;
						} 
						else if (player == 2) {
							other = &p2;
						}
						else {
							throw "Invalid Input";
						}
						if (iss >> other_card) {
							if (other_card == 'r') {
								curr_player->use_on_ritual(card-1, *other);
							}
							else {
								int other_card_int = other_card - '0';
								curr_player->use_on_minion(card-1, *other, other_card_int-1);
							}
						}
					} 
					else {
						curr_player->use(card-1);
					}
				}
			}
			else if (sepcmd == "inspect") { // print information of the card
				// do proper cin stuff here
				int i;
				iss >> i;
				// calls inspect method
				inspect(*curr_player, i-1);
			}
			else if (sepcmd == "hand") {
				// calls displayhand method from textdisplay
				displayhand(*curr_player);
			}
			else if (sepcmd == "board") {
				// calls displayboard method from textdisplay
				displayboard(p1, p2);
			}

			// TESTING FEATURES
			else if (sepcmd == "draw") {
				// draw a card from the deck
				curr_player->draw();
					
			}
			else if (sepcmd == "discard") {
				// do proper cin stuff here
				int card;
				iss >> card;
				// remove a card from the player's hand
				curr_player->discard(card-1);
			}
			else {}
			// check win condition
			if (p1.isDead()) {
				cout << p2.get_name() << " wins!" << endl;
				break;
			}
			if (p2.isDead()) {
				cout << p1.get_name() << " wins!" << endl;
				break;
			}

		}
		catch (char const* &ErrorMsg) {
			cout << ErrorMsg << endl;
			continue;

		}
		catch (string &ErrorMsg) {
			cout << ErrorMsg << endl;
			continue;

		}
	}
}
