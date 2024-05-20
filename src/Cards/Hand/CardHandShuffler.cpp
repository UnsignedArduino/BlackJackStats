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

  // Fisher-Yates/Knuth shuffle algorithm
  // From GitHub Copilot lol
  auto rng = cardhand_shuffle_rng_t(seed);

  for (card_hand_index_t i = this->getHandSize() - 1; i > 0; i--) {
    std::uniform_int_distribution<card_hand_index_t> dist(0, i);
    card_hand_index_t randomIndex = dist(rng);
    std::swap(this->hand[i], this->hand[randomIndex]);
  }

  return CARD_ACTION_RESULT_SUCCESS;
}
