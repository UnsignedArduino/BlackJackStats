#include "algorithm.h"

// clang-format off
blackjack_game_move_t perfect_algorithm_matrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE] = {
// Hard 5-20          Soft A2-A9 Pair AA-TT      Dealer's face up card
  "hhhhhhdhhhhhssss" "hhhhhhss" "phhhhhhpss", // A
  "hhhhhddhssssssss" "hhhhhdss" "ppphdpppps", // 2
  "hhhhdddhssssssss" "hhhhddss" "ppphdpppps", // 3
  "hhhhdddsssssssss" "hhddddss" "ppphdpppps", // 4
  "hhhhdddsssssssss" "ddddddss" "ppppdpppps", // 5
  "hhhhdddsssssssss" "ddddddds" "ppppdpppps", // 6
  "hhhhhddhhhhhssss" "hhhhhsss" "ppphdhppss", // 7
  "hhhhhddhhhhhssss" "hhhhhsss" "phhhdhhpps", // 8
  "hhhhhddhhhhhssss" "hhhhhhss" "phhhdhhpps", // 9
  "hhhhhhdhhhhhssss" "hhhhhhss" "phhhhhhpss"  // T
};
// clang-format on

blackjack_game_move_t getMoveFromMatrix(blackjack_game_move_t matrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE], card_t dealerCard, BlackjackHand playerHand) {
  const blackjack_game_move_t* matrixRow = matrix[min(dealerCard & CARD_RANK_MASK, 10) - 1];
  const card_t firstCard = playerHand.getCardFromTop();
  const card_t lastCard = playerHand.getCardFromBottom();
  if (firstCard == lastCard && playerHand.getHandSize() == 2) { // Pair
    return matrixRow[16 + 8 + (firstCard & CARD_RANK_MASK) - 1];
  } else if (playerHand.getSoftHandValue() != playerHand.getHardHandValue()) { // Soft hand
    return matrixRow[16 + (playerHand.getHardHandValue() - 3)];
  } else { // Hard hand
    return matrixRow[playerHand.getHardHandValue() - 5];
  }
  return BLACKJACK_GAME_MOVE_STAND;
}
