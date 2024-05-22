#include "BlackjackGame.h"

BlackjackGame::BlackjackGame() {
  this->deck = CardHand();
  this->dealerHand = BlackjackHand();
  this->playerHand = BlackjackHand();
}

void BlackjackGame::setup(uint32_t seed) {
  this->deck.clearHand();
  this->deck.fillHandWithDeck();
  this->deck.shuffleHand(seed);

  this->dealerHand.clearHand();
  this->dealerHand.addCardToTop(this->deck.drawCardFromTop());
  this->dealerHand.addCardToTop(this->deck.drawCardFromTop());

  this->playerHand.clearHand();
  this->playerHand.addCardToTop(this->deck.drawCardFromTop());
  this->playerHand.addCardToTop(this->deck.drawCardFromTop());
}

blackjack_game_state_t BlackjackGame::gameState() {
  const card_t playerHand = this->playerHand.getHandValue();
  const card_t dealerHand = this->dealerHand.getHandValue();

  if (playerHand > 21) {
    return BLACKJACK_GAME_PLAYER_LOSS;
  } else if (dealerHand > 21) {
    return BLACKJACK_GAME_PLAYER_WIN;
  } else if (playerHand == 21) {
    return BLACKJACK_GAME_PLAYER_WIN;
  } else if (dealerHand == 21) {
    return BLACKJACK_GAME_PLAYER_LOSS;
  } else if (!this->playerDone) {
    return BLACKJACK_GAME_IN_PROGRESS;
  } else if (playerHand > dealerHand) {
    return BLACKJACK_GAME_PLAYER_WIN;
  } else if (playerHand < dealerHand) {
    return BLACKJACK_GAME_PLAYER_LOSS;
  } else {
    return BLACKJACK_GAME_DRAW;
  }
}

// void BlackjackGame::playerHit() {
//   this->playerHand.addCardToBottom(this->deck.drawCardFromTop());
//   if (this->playerHand.getHandValue() >= 21) {
//     this->playerDone = true;
//   }
// }

// void BlackjackGame::playerStand() {
//   this->playerDone = true;
//   while (this->dealerHand.getHandValue() < 17) {
//     this->dealerHand.addCardToBottom(this->deck.drawCardFromTop());
//   }
// }
