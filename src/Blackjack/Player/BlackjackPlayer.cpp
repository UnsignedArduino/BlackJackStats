#include "BlackjackPlayer.h"

BlackjackPlayer::BlackjackPlayer() {
  this->hands[0] = new BlackjackHand();
  this->handsStood[0] = false;
  this->handsDoubledDown[0] = false;
  for (uint8_t i = 1; i < PLAYER_SPLITS_MAX; i++) {
    this->hands[i] = nullptr;
    this->handsStood[i] = false;
    this->handsDoubledDown[i] = false;
  }
}

void BlackjackPlayer::printHands() {
  printf("Player hands:");
  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (this->hands[i] == nullptr) {
      break;
    }
    printf("\nHand %d: ", i + 1);
    for (card_hand_index_t j = 0; j < CARDHAND_MAX_SIZE; j++) {
      if (this->hands[i]->hand[j] == CARD_NULL) {
        break;
      }
      printCard(this->hands[i]->hand[j]);
    }
    printf("(%d", this->hands[i]->getSoftHandValue());
    if (this->hands[i]->getSoftHandValue() != this->hands[i]->getHardHandValue()) {
      printf(" / %d", this->hands[i]->getHardHandValue());
    }
    if (this->handsStood[i]) {
      printf(" - stood");
    }
    if (this->handsDoubledDown[i]) {
      printf(" - doubled");
    }
    printf(")");
  }
}

uint8_t BlackjackPlayer::getHandCount() {
  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (this->hands[i] == nullptr) {
      return i;
    }
  }
  return PLAYER_SPLITS_MAX;
}

blackjack_player_action_result_t BlackjackPlayer::hit(uint8_t handIndex, card_t card, bool doubleDown /* = false*/) {
  if (this->handsStood[handIndex]) {
    return BLACKJACK_PLAYER_ACTION_RESULT_ALREADY_STOOD;
  } else if (this->handsDoubledDown[handIndex]) {
    return BLACKJACK_PLAYER_ACTION_RESULT_ALREADY_DOUBLED_DOWN;
  } else if (this->hands[handIndex]->addCardToBottom(card) == CARD_ACTION_RESULT_SUCCESS) {
    if (this->hands[handIndex]->getSoftHandValue() > 21) {
      this->handsStood[handIndex] = true;
    }
    if (doubleDown) {
      this->handsDoubledDown[handIndex] = true;
      this->stand(handIndex);
    }
    return BLACKJACK_PLAYER_ACTION_RESULT_SUCCESS;
  } else {
    return BLACKJACK_PLAYER_ACTION_RESULT_HAND_FULL;
  }
}

blackjack_player_action_result_t BlackjackPlayer::stand(uint8_t handIndex) {
  if (this->handsStood[handIndex]) {
    return BLACKJACK_PLAYER_ACTION_RESULT_ALREADY_STOOD;
  } else {
    this->handsStood[handIndex] = true;
    return BLACKJACK_PLAYER_ACTION_RESULT_SUCCESS;
  }
}

blackjack_player_game_state_t BlackjackPlayer::gameState() {
  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (!this->handsStood[i] && (this->hands[i] != nullptr && this->hands[i]->getSoftHandValue() < 21)) {
      return BLACKJACK_PLAYER_GAME_STATE_IN_PROGRESS;
    }
  }
  return BLACKJACK_PLAYER_GAME_STATE_PLAYER_FINISHED;
}

int8_t BlackjackPlayer::getNextHandIndex() {
  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (!this->handsStood[i] && this->hands[i] != nullptr && this->hands[i]->getSoftHandValue() < 21) {
      return i;
    }
  }
  return -1;
}

void BlackjackPlayer::splitHand(uint8_t handIndex) {
  uint8_t nextHandIndex = this->getHandCount();
  this->hands[nextHandIndex] = new BlackjackHand();
  this->hands[nextHandIndex]->addCardToTop(this->hands[handIndex]->drawCardFromTop());
}
