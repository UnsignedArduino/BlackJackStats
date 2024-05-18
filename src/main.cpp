#include "Cards/Hand/CardHand.h"

int main() {
  CardHand hand = CardHand();
  hand.fillHandWithDeck();
  hand.printHand();

  return 0;
}
