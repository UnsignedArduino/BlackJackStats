#include "Cards/Hand/CardHand.h"
#include <cstdio>

int main() {
  CardHand hand = CardHand();
  hand.fillHandWithDeck();

  for (uint8_t i = 0; i < 10; i++) {
    printf("Seed: %d\n", i);
    hand.shuffleHand(i);
    hand.printHand();
  }

  return 0;
}
