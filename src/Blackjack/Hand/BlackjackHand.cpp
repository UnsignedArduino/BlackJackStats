#include "BlackjackHand.h"

void printCardAndValue(card_t card) {
  printCard(card);
  if ((card & CARD_RANK_MASK) == CARD_RANK_ACE) {
    printf("(11 / 1)");
  } else {
    printf("(%f)", min(card & CARD_RANK_MASK, 10));
  }
}

card_t BlackjackHand::getSoftHandValue() {
  card_t value = 0;
  uint8_t numberOfAces = 0;

  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    if ((this->hand[i] & CARD_RANK_MASK) == CARD_RANK_ACE) {
      numberOfAces++;
      value += 10;
    }
    value += min(this->hand[i] & CARD_RANK_MASK, 10);
  }

  while (value > 21 && numberOfAces > 0) {
    value -= 10;
    numberOfAces--;
  }

  return value;
}

card_t BlackjackHand::getHardHandValue() {
  card_t value = 0;

  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    value += min(this->hand[i] & CARD_RANK_MASK, 10);
  }

  return value;
}

bool BlackjackHand::canSplit() {
  if (this->getHandSize() != 2) {
    return false;
  }
  return fmin(this->hand[0] & CARD_RANK_MASK, 10) == min(this->hand[1] & CARD_RANK_MASK, 10);
}

void BlackjackHand::printHand() {
  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    if (this->hand[i] == CARD_NULL) {
      break;
    }
    printCard(this->hand[i]);
  }
  if (this->getSoftHandValue() != this->getHardHandValue()) {
    printf("(%d / %d)", this->getSoftHandValue(), this->getHardHandValue());
  } else {
    printf("(%d)", this->getSoftHandValue());
  }
}
