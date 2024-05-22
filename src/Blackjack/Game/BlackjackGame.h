#ifndef BLACKJACKSTATS_GAME_H
#define BLACKJACKSTATS_GAME_H

#include "../Player/BlackjackPlayer.h"

// Only one player to keep it simple
class BlackjackGame {
  public:
    BlackjackGame(uint32_t seed);
    ~BlackjackGame() = default;

    BlackjackPlayer player;
    BlackjackHand dealerHand;
    CardHand deck;
};

#endif//BLACKJACKSTATS_GAME_H
