#ifndef BLACKJACKSTATS_BLACKJACKPLAYER_H
#define BLACKJACKSTATS_BLACKJACKPLAYER_H

#include "../Hand/BlackjackHand.h"

const uint8_t PLAYER_SPLITS_MAX = 16;

typedef int8_t blackjack_player_action_result_t;

const blackjack_player_action_result_t BLACKJACK_PLAYER_ACTION_RESULT_SUCCESS = 0;
const blackjack_player_action_result_t BLACKJACK_PLAYER_ACTION_RESULT_HAND_FULL = -1;
const blackjack_player_action_result_t BLACKJACK_PLAYER_ACTION_RESULT_ALREADY_STOOD = -2;
const blackjack_player_action_result_t BLACKJACK_PLAYER_ACTION_RESULT_ALREADY_DOUBLED_DOWN = -3;

typedef int8_t blackjack_player_game_state_t;

const blackjack_player_game_state_t BLACKJACK_PLAYER_GAME_STATE_IN_PROGRESS = 127;
const blackjack_player_game_state_t BLACKJACK_PLAYER_GAME_STATE_PLAYER_FINISHED = 0;

class BlackjackPlayer {
  public:
    BlackjackPlayer();
    ~BlackjackPlayer() = default;

    uint8_t getHandCount();

    void printHands();

    blackjack_player_action_result_t hit(uint8_t handIndex, card_t card, bool doubleDown = false);
    blackjack_player_action_result_t stand(uint8_t handIndex);

    blackjack_player_game_state_t gameState();
    int8_t getNextHandIndex();

    void splitHand(uint8_t handIndex);

    BlackjackHand *hands[PLAYER_SPLITS_MAX];
    bool handsStood[PLAYER_SPLITS_MAX];
    bool handsDoubledDown[PLAYER_SPLITS_MAX];
};


#endif//BLACKJACKSTATS_BLACKJACKPLAYER_H
