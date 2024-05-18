#include "Cards.h"
#include "stdio.h"

void printCard(card_t card) {
  if (card == CARD_NULL) {
    printf("00  ");
    return;
  }
  if ((card & CARD_SUIT_MASK) == CARD_SUIT_HEARTS_FLAG) {
    printf("H");
  } else if ((card & CARD_SUIT_MASK) == CARD_SUIT_DIAMONDS_FLAG) {
    printf("D");
  } else if ((card & CARD_SUIT_MASK) == CARD_SUIT_CLUBS_FLAG) {
    printf("C");
  } else if ((card & CARD_SUIT_MASK) == CARD_SUIT_SPADES_FLAG) {
    printf("S");
  }
  if ((card & CARD_RANK_MASK) == CARD_RANK_ACE) {
    printf("A");
  } else if ((card & CARD_RANK_MASK) == CARD_RANK_JACK) {
    printf("J");
  } else if ((card & CARD_RANK_MASK) == CARD_RANK_QUEEN) {
    printf("Q");
  } else if ((card & CARD_RANK_MASK) == CARD_RANK_KING) {
    printf("K");
  } else {
    printf("%d", card & CARD_RANK_MASK);
  }
  if ((card & CARD_RANK_MASK) != 10) {
    printf(" ");
  }
  printf(" ");
}