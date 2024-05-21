#include "BlackjackHand.h"
#include "../../Cards/Hand/CardHand.h"

void printCardAndValue(card_t card) {
  printCard(card);
  if ((card & CARD_RANK_MASK) == CARD_RANK_ACE) {
    printf(" (11 / 1)");
  } else {
    printf(" (%d)", card & CARD_RANK_MASK);
  }
}

card_t BlackjackHand::getHardHandValue() {
  card_t value = 0;

  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    value += fmin(this->hand[i] & CARD_RANK_MASK, 10);
  }

  return value;
}

card_t BlackjackHand::getHandValue() {
  card_t value = 0;
  uint8_t numberOfAces = 0;

  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    if ((this->hand[i] & CARD_RANK_MASK) == CARD_RANK_ACE) {
      numberOfAces++;
      value += 10;
    }
    value += fmin(this->hand[i] & CARD_RANK_MASK, 10);
  }

  while (value > 21 && numberOfAces > 0) {
    value -= 10;
    numberOfAces--;
  }

  return value;
}

void BlackjackHand::printHand() {
  for (card_hand_index_t i = 0; i < CARDHAND_MAX_SIZE; i++) {
    if (this->hand[i] == CARD_NULL) {
      break;
    }
    printCard(this->hand[i]);
  }
  if (this->getHandValue() != this->getHardHandValue()) {
    printf(" (%d / %d)", this->getHandValue(), this->getHardHandValue());
  } else {
    printf(" (%d)", this->getHardHandValue());
  }
}
