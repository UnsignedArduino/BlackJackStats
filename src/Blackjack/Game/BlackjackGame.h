#ifndef BLACKJACKSTATS_GAME_H
#define BLACKJACKSTATS_GAME_H

#include "../Player/BlackjackPlayer.h"

typedef int8_t blackjack_game_state_t;
const blackjack_game_state_t BLACKJACK_GAME_STATE_IN_PROGRESS = 127;
const blackjack_game_state_t BLACKJACK_GAME_STATE_PLAYER_FINISHED = 0;

// Only one player to keep it simple
class BlackjackGame {
  public:
    explicit BlackjackGame(uint32_t seed);
    ~BlackjackGame() = default;

    blackjack_game_state_t gameState();
    int8_t moneyFlow(int8_t hand = -1);

    void dealerHits();

    BlackjackPlayer player;
    BlackjackHand dealerHand;
    CardHand deck;
};

#endif//BLACKJACKSTATS_GAME_H
