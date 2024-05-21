#include "../Hand/BlackjackHand.h"

#ifndef BLACKJACKSTATS_GAME_H
  #define BLACKJACKSTATS_GAME_H

typedef int8_t blackjack_game_result_t;

const blackjack_game_result_t WIN = 1;
const blackjack_game_result_t DRAW = 0;
const blackjack_game_result_t LOSE = -1;
const blackjack_game_result_t IN_PROGRESS = 2;

// Only one player to keep it simple
class BlackjackGame {
  public:
    BlackjackGame();
    ~BlackjackGame() = default;

    void setup(uint32_t seed);

    BlackjackHand playerHand;
    BlackjackHand dealerHand;

    void hit() {
      this->playerHand.addCardToBottom(this->deck.drawCardFromTop());
      if (this->playerHand.getHandValue() >= 21) {
        this->playerIsDone = true;
      }
    }

    void stand() {
      while (this->dealerHand.getHandValue() < 17) {
        this->dealerHand.addCardToBottom(this->deck.drawCardFromTop());
      }
      this->playerIsDone = true;
    }

    blackjack_game_result_t checkGameResult() {
      if (!this->playerIsDone) {
        return IN_PROGRESS;
      }
      const card_t playerHandValue = this->playerHand.getHandValue();
      const card_t dealerHandValue = this->dealerHand.getHandValue();
      if (playerHandValue > 21) {// NOLINT(*-branch-clone)
        return LOSE;
      } else if (dealerHandValue > 21) {// NOLINT(*-branch-clone)
        return WIN;
      } else if (playerHandValue > dealerHandValue) {
        return WIN;
      } else if (playerHandValue == dealerHandValue) {
        return DRAW;
      } else {
        return LOSE;
      }
    }

  private:
    CardHand deck;
    bool playerIsDone = false;
};

#endif//BLACKJACKSTATS_GAME_H
