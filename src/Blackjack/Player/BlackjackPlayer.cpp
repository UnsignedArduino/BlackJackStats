#include "BlackjackPlayer.h"

BlackjackPlayer::BlackjackPlayer() {
  this->hands[0] = new BlackjackHand();
  for (uint8_t i = 1; i < PLAYER_SPLITS_MAX; i ++) {
    this->hands[i] = nullptr;
  }
}

void BlackjackPlayer::printHands() {
  printf("Player hands:\n");
  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (this->hands[i] == nullptr) {
      break;
    }
    printf("Hand %d: ", i);
    for (card_hand_index_t j = 0; j < CARDHAND_MAX_SIZE; j++) {
      if (this->hands[i]->hand[j] == CARD_NULL) {
        break;
      }
      printCard(this->hands[i]->hand[j]);
    }
    printf("(%d)\n", this->hands[i]->getHandValue());
  }
}
