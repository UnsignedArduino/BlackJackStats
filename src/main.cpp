#include "Cards/Cards.h"
#include <cstdio>

int main() {
  for (card_t i = 1; i <= 13; i++) {
    printCard(CARD_SUIT_HEARTS_FLAG | i);
    printCard(CARD_SUIT_DIAMONDS_FLAG | i);
    printCard(CARD_SUIT_CLUBS_FLAG | i);
    printCard(CARD_SUIT_SPADES_FLAG | i);
    printf("\n");
  }

  return 0;
}
