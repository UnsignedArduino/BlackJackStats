#include "CardHand.h"
#include <random>

#ifndef CARDHAND_SHUFFLE_RNG
  #define CARDHAND_SHUFFLE_RNG std::mt19937
//  #define CARDHAND_SHUFFLE_RNG std::minstd_rand  // 0.01 ms faster but less random
#endif//CARDHAND_SHUFFLE_RNG

typedef CARDHAND_SHUFFLE_RNG cardhand_shuffle_rng_t;

card_hand_action_result_t CardHand::shuffleHand(uint32_t seed) {
  if (this->getHandSize() == 0) {
    return CARD_ACTION_RESULT_HAND_EMPTY;
  }

  card_t newHand[CARDHAND_MAX_SIZE];
  card_hand_index_t newHandIndex = 0;

  auto rng = cardhand_shuffle_rng_t(seed);

  while (this->getHandSize() > 1) {
    std::uniform_int_distribution<card_hand_index_t> dist(0, this->getHandSize() - 1);
    card_hand_index_t randomIndex = dist(rng);
    newHand[newHandIndex] = this->drawCard(randomIndex);
    newHandIndex++;
  }

  newHand[newHandIndex] = this->drawCardFromTop();

  this->clearHand();

  for (card_hand_index_t i = 0; i < newHandIndex + 1; i++) {
    this->addCardToTop(newHand[i]);
  }

  return CARD_ACTION_RESULT_SUCCESS;
}
