#include "CardHand.h"

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
