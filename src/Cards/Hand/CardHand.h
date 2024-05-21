#include "../Cards.h"
#include <random>

#ifndef CARDHAND_MAX_SIZE
  #define CARDHAND_MAX_SIZE 52
typedef int16_t card_hand_index_t;
#endif//CARDHAND_MAX_SIZE

//#define CARDHAND_DEBUG 1

#ifndef CARDHAND_DEBUG
  #define CARDHAND_DEBUG 0
#endif//CARDHAND_DEBUG

#if CARDHAND_DEBUG == 1
  #include <cstdio>
  #define CARDHAND_DEBUG_PRINT(...) printf(__VA_ARGS__)
  #define CARDHAND_DEBUG_PRINT_CARD(card) printCard(card)
#else
  #define CARDHAND_DEBUG_PRINT(...)
  #define CARDHAND_DEBUG_PRINT_CARD(card)
#endif//CARDHAND_DEBUG

#ifndef CARDHAND_SHUFFLE_RNG
  #define CARDHAND_SHUFFLE_RNG std::mt19937
//  #define CARDHAND_SHUFFLE_RNG std::minstd_rand  // 0.01 ms faster but less random
#endif//CARDHAND_SHUFFLE_RNG

#ifndef BLACKJACKSTATS_CARDHAND_H
  #define BLACKJACKSTATS_CARDHAND_H

typedef uint8_t card_hand_action_result_t;
typedef CARDHAND_SHUFFLE_RNG cardhand_shuffle_rng_t;

const card_hand_action_result_t CARD_ACTION_RESULT_SUCCESS = 0;
const card_hand_action_result_t CARD_ACTION_RESULT_HAND_FULL = 1;
const card_hand_action_result_t CARD_ACTION_RESULT_HAND_EMPTY = 2;
const card_hand_action_result_t CARD_ACTION_RESULT_HAND_INVALID_INDEX = 3;

class CardHand {
  public:
    CardHand();
    ~CardHand() = default;

    card_hand_action_result_t clearHand();
    card_hand_action_result_t fillHandWithDeck();
    card_hand_action_result_t shuffleHand(uint32_t seed);

    card_hand_index_t getHandSize();

    card_hand_action_result_t addCardToTop(card_t card);
    card_hand_action_result_t addCardToBottom(card_t card);
    card_hand_action_result_t insertCard(card_t card, card_hand_index_t index);

    card_t getCardFromTop();
    card_t getCardFromBottom();
    card_t getCard(card_hand_index_t index);

    card_t drawCardFromTop();
    card_t drawCardFromBottom();
    card_t drawCard(card_hand_index_t index);

    virtual void printHand();
    void printAsArray();

    card_t hand[CARDHAND_MAX_SIZE];

  private:
    card_hand_action_result_t compactHandUp();
    card_hand_action_result_t compactHandDown();

    card_hand_action_result_t shiftHandUp();
    card_hand_action_result_t shiftHandDown();
};


#endif//BLACKJACKSTATS_CARDHAND_H
