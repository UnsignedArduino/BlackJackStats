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
