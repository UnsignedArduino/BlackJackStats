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
