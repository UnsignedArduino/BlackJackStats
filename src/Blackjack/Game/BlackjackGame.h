#include "../Hand/BlackjackHand.h"

#ifndef BLACKJACKSTATS_GAME_H
  #define BLACKJACKSTATS_GAME_H

typedef int8_t blackjack_game_state_t;

const blackjack_game_state_t BLACKJACK_GAME_IN_PROGRESS = 0;
const blackjack_game_state_t BLACKJACK_GAME_PLAYER_WIN = 1;
const blackjack_game_state_t BLACKJACK_GAME_PLAYER_LOSS = 2;
const blackjack_game_state_t BLACKJACK_GAME_DRAW = 3;

// Only one player to keep it simple
class BlackjackGame {
  public:
    BlackjackGame();
    ~BlackjackGame() = default;

    void setup(uint32_t seed);

    blackjack_game_state_t gameState();

    void playerHit();
    void playerStand();

    BlackjackHand playerHand;
    BlackjackHand dealerHand;
    CardHand deck;

  private:
    bool playerDone = false;
};

#endif//BLACKJACKSTATS_GAME_H
