#ifndef BLACKJACKSTATS_BLACKJACKHAND_H
#define BLACKJACKSTATS_BLACKJACKHAND_H

#include "../../Cards/Hand/CardHand.h"
#include "../../helpers.h"

void printCardAndValue(card_t card);

class BlackjackHand : public CardHand {
  public:
    BlackjackHand() = default;
    ~BlackjackHand() = default;

    card_t getSoftHandValue();
    card_t getHardHandValue();
    bool canSplit();

    void printHand() override;

  private:
};


#endif //BLACKJACKSTATS_BLACKJACKHAND_H
