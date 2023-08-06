#include "effect.h"
#include "player.h"
#include <memory>
#include "minion.h"



void Effect::start_turn_trigger(Player &active) {}

void Effect::end_turn_trigger(Player &active) {}

void Effect::enter_play_trigger(Player &whoplayed, Player &whoowned, std::shared_ptr<Minion> whoentered) {}

void Effect::attack_player_trigger(std::shared_ptr<Minion> whoattacked, Player &whogetsattacked) {}

