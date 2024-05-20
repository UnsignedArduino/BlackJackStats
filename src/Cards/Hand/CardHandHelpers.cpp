#include "CardHand.h"
#include <cstdio>

card_hand_action_result_t CardHand::compactHandUp() {
  CARDHAND_DEBUG_PRINT("Compacting hand up\n");
  for (card_hand_index_t i = 1; i < CARDHAND_MAX_SIZE; i++) {
    card_hand_index_t moveTo = i;
    while (this->hand[moveTo - 1] == CARD_NULL && (moveTo - 1) >= 0) {
      moveTo--;
    }
    if (moveTo == i) {
      continue;
    }
    this->hand[moveTo] = this->hand[i];
    this->hand[i] = CARD_NULL;
  }
  return CARD_ACTION_RESULT_SUCCESS;
}

card_hand_action_result_t CardHand::compactHandDown() {
  CARDHAND_DEBUG_PRINT("Compacting hand down\n");
  for (card_hand_index_t i = CARDHAND_MAX_SIZE - 2; i >= 0; i--) {
    card_hand_index_t moveTo = i;
    while (this->hand[moveTo + 1] == CARD_NULL && (moveTo + 1) <= CARDHAND_MAX_SIZE - 1) {
      moveTo++;
    }
    if (moveTo == i) {
      continue;
    }
    this->hand[moveTo] = this->hand[i];
    this->hand[i] = CARD_NULL;
  }
  return CARD_ACTION_RESULT_SUCCESS;
}

card_hand_action_result_t CardHand::shiftHandUp() {
  CARDHAND_DEBUG_PRINT("Shifting hand up\n");
  if (this->hand[0] != CARD_NULL) {
    return CARD_ACTION_RESULT_HAND_FULL;
  }
  for (card_hand_index_t i = 1; i < CARDHAND_MAX_SIZE; i++) {
    if (this->hand[i - 1] == CARD_NULL) {
      this->hand[i - 1] = this->hand[i];
      this->hand[i] = CARD_NULL;
    }
  }
  return CARD_ACTION_RESULT_SUCCESS;
}

card_hand_action_result_t CardHand::shiftHandDown() {
  CARDHAND_DEBUG_PRINT("Shifting hand down\n");
  if (this->hand[CARDHAND_MAX_SIZE - 1] != CARD_NULL) {
    return CARD_ACTION_RESULT_HAND_FULL;
  }
  for (card_hand_index_t i = CARDHAND_MAX_SIZE - 2; i >= 0; i--) {
    if (this->hand[i + 1] == CARD_NULL) {
      this->hand[i + 1] = this->hand[i];
      this->hand[i] = CARD_NULL;
    }
  }
  return CARD_ACTION_RESULT_SUCCESS;
}

void CardHand::printHand() {
  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    printCard(this->hand[i]);
  }
  printf("\n");
}

void CardHand::printAsArray() {
  printf("{");
  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    if (i != 0) {
      printf(", ");
    }
    printf("0x%02x", this->hand[i]);
  }
  printf("}\n");
}
