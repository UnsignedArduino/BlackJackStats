#include "BlackjackGame.h"

BlackjackGame::BlackjackGame(uint32_t seed) {
  this->deck = CardHand();
  this->dealerHand = BlackjackHand();
  this->player = BlackjackPlayer();

  this->deck.fillHandWithDeck();
  this->deck.shuffleHand(seed);

  this->dealerHand.addCardToTop(this->deck.drawCardFromTop());
  this->dealerHand.addCardToTop(this->deck.drawCardFromTop());

  this->player.hands[0]->addCardToTop(this->deck.drawCardFromTop());
  this->player.hands[0]->addCardToTop(this->deck.drawCardFromTop());
}

blackjack_game_state_t BlackjackGame::gameState() {
  if (this->player.gameState() == BLACKJACK_PLAYER_GAME_STATE_PLAYER_FINISHED) {
    return BLACKJACK_GAME_STATE_PLAYER_FINISHED;
  } else {
    return BLACKJACK_GAME_STATE_IN_PROGRESS;
  }
}

int8_t BlackjackGame::moneyFlow(int8_t hand /* = -1*/) {
  if (hand >= 0 && hand < this->player.getHandCount()) {
    int8_t thisFlow = 0;
    if (this->player.hands[hand]->getSoftHandValue() > 21) {
      thisFlow = -1;
    } else if (this->dealerHand.getSoftHandValue() > 21) {
      thisFlow = 1;
    } else if (this->player.hands[hand]->getSoftHandValue() > this->dealerHand.getSoftHandValue()) {
      thisFlow = 1;
    } else if (this->player.hands[hand]->getSoftHandValue() < this->dealerHand.getSoftHandValue()) {
      thisFlow = -1;
    }
    if (this->player.handsDoubledDown[hand]) {
      thisFlow *= 2;
    }
    return thisFlow;
  }
  int8_t flow = 0;
  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (this->player.hands[i] == nullptr) {
      continue;
    }
    flow += this->moneyFlow(i);
  }
  return flow;
}

void BlackjackGame::dealerHits() {
  while (this->dealerHand.getSoftHandValue() < 17) {
    this->dealerHand.addCardToBottom(this->deck.drawCardFromTop());
  }
}
