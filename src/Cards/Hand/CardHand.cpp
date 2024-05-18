#include "CardHand.h"

CardHand::CardHand() {// NOLINT(*-pro-type-member-init)
  this->clearHand();
}

card_hand_action_result_t CardHand::clearHand() {
  for (card_t &i: this->hand) {
    i = CARD_NULL;
  }
  CARDHAND_DEBUG_PRINT("Hand cleared\n");
  return CARD_ACTION_RESULT_SUCCESS;
}

card_hand_action_result_t CardHand::fillHandWithDeck() {
  for (const card_t &suit: CARD_SUITS) {
    for (const card_t &rank: CARD_RANKS) {
      this->addCardToBottom(suit | rank);
    }
  }
  return CARD_ACTION_RESULT_SUCCESS;
}

card_hand_index_t CardHand::getHandSize() {
  card_hand_index_t size = 0;
  for (card_t i: this->hand) {
    if (i != CARD_NULL) {
      size++;
    }
  }
  return size;
}

card_hand_action_result_t CardHand::addCardToTop(card_t card) {
  return this->insertCard(card, 0);
}

card_hand_action_result_t CardHand::addCardToBottom(card_t card) {
  const card_hand_action_result_t result = this->insertCard(card, CARDHAND_MAX_SIZE - 1);
  if (result != CARD_ACTION_RESULT_SUCCESS) {
    return result;
  }
  this->compactHandUp();
  return CARD_ACTION_RESULT_SUCCESS;
}

card_hand_action_result_t CardHand::insertCard(card_t card, card_hand_index_t index) {
  this->compactHandUp();
  if (this->hand[CARDHAND_MAX_SIZE - 1] != CARD_NULL) {
    return CARD_ACTION_RESULT_HAND_FULL;
  }
  if (index < 0 || index >= CARDHAND_MAX_SIZE) {
    return CARD_ACTION_RESULT_HAND_INVALID_INDEX;
  }
  for (card_hand_index_t i = CARDHAND_MAX_SIZE - 2; i >= index; i--) {
    if (this->hand[i + 1] == CARD_NULL) {
      this->hand[i + 1] = this->hand[i];
      this->hand[i] = CARD_NULL;
    }
  }
  this->hand[index] = card;
  return CARD_ACTION_RESULT_SUCCESS;
}

card_t CardHand::getCardFromTop() {
  return this->hand[0];
}

card_t CardHand::getCardFromBottom() {
  for (card_hand_index_t i = CARDHAND_MAX_SIZE - 1; i >= 0; i--) {
    if (this->hand[i] != CARD_NULL) {
      return this->hand[i];
    }
  }
  return CARD_NULL;
}

card_t CardHand::getCard(card_hand_index_t index) {
  if (index < 0 || index >= CARDHAND_MAX_SIZE) {
    return CARD_NULL;
  }
  return this->hand[index];
}

card_t CardHand::drawCardFromTop() {
  const card_t card = this->hand[0];
  this->hand[0] = CARD_NULL;
  this->shiftHandUp();
  return card;
}

card_t CardHand::drawCardFromBottom() {
  card_t card = CARD_NULL;
  for (card_hand_index_t i = CARDHAND_MAX_SIZE - 1; i >= 0; i--) {
    if (this->hand[i] != CARD_NULL) {
      card = this->hand[i];
      this->hand[i] = CARD_NULL;
      break;
    }
  }
  return card;
}

card_t CardHand::drawCard(card_hand_index_t index) {
  if (index < 0 || index >= CARDHAND_MAX_SIZE) {
    return CARD_NULL;
  }
  const card_t card = this->hand[index];
  this->hand[index] = CARD_NULL;
  this->compactHandUp();
  return card;
}
