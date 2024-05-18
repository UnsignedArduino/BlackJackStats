#include "Cards.h"
#include "stdio.h"

void printCard(card_t card) {
  if ((card & CARD_SUIT_MASK) == CARD_SUIT_HEARTS_FLAG) {
    printf("H");
  } else if ((card & CARD_SUIT_MASK) == CARD_SUIT_DIAMONDS_FLAG) {
    printf("D");
  } else if ((card & CARD_SUIT_MASK) == CARD_SUIT_CLUBS_FLAG) {
    printf("C");
  } else if ((card & CARD_SUIT_MASK) == CARD_SUIT_SPADES_FLAG) {
    printf("S");
  } else {
    printf("0");
  }
  if ((card & CARD_VALUE_MASK) == CARD_VALUE_ACE) {
    printf("A");
  } else if ((card & CARD_VALUE_MASK) == CARD_VALUE_JACK) {
    printf("J");
  } else if ((card & CARD_VALUE_MASK) == CARD_VALUE_QUEEN) {
    printf("Q");
  } else if ((card & CARD_VALUE_MASK) == CARD_VALUE_KING) {
    printf("K");
  } else {
    printf("%d", card & CARD_VALUE_MASK);
  }
  if ((card & CARD_VALUE_MASK) != 10) {
    printf(" ");
  }
  printf(" ");
}