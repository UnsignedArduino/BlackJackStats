#include "../../Cards/Hand/CardHand.h"

#ifndef BLACKJACKSTATS_BLACKJACKHAND_H
  #define BLACKJACKSTATS_BLACKJACKHAND_H

void printCardAndValue(card_t card);

class BlackjackHand : public CardHand {
  public:
    BlackjackHand() = default;
    ~BlackjackHand() = default;

    card_t getHandValue();

    void printHand();

  private:
};


#endif//BLACKJACKSTATS_BLACKJACKHAND_H
