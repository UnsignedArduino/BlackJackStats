#ifndef BLACKJACKSTATS_BLACKJACKPLAYER_H
#define BLACKJACKSTATS_BLACKJACKPLAYER_H

#include "../Hand/BlackjackHand.h"

const uint8_t PLAYER_SPLITS_MAX = 16;

class BlackjackPlayer {
  public:
    BlackjackPlayer();
    ~BlackjackPlayer() = default;

    uint8_t getHandCount();

    void printHands();

    BlackjackHand *hands[PLAYER_SPLITS_MAX];
};


#endif//BLACKJACKSTATS_BLACKJACKPLAYER_H
