#ifndef BLACKJACKSTATS_ALGORITHM_H
#define BLACKJACKSTATS_ALGORITHM_H

#include "Blackjack/Hand/BlackjackHand.h"
#include "Cards/Hand/CardHand.h"

typedef char blackjack_game_move_t;
const blackjack_game_move_t BLACKJACK_GAME_MOVE_STAND = 's';
const blackjack_game_move_t BLACKJACK_GAME_MOVE_HIT = 'h';
const blackjack_game_move_t BLACKJACK_GAME_MOVE_SPLIT = 'p';
const blackjack_game_move_t BLACKJACK_GAME_MOVE_DOUBLE_DOWN = 'd';

// T = 10, J, Q, K (they are all worth ten)
// First dimension is the dealer's face up card value
//   2, 3, 4, 5, 6, 7, 8, 9, T, A
// Second dimension is the player's hand value
//   The first 16 values are the hard hand values
//     5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
//   The next 8 values are the soft hand values
//     A2, A3, A4, A5, A6, A7, A8, A9
//   The last 10 values are the pair values
//     2, 3, 4, 5, 6, 7, 8, 9, T, A
// The result is the move to make
const uint8_t AM_DEALERS_SIZE = 10;
const uint8_t AM_PLAYERS_SIZE = 16 + 8 + 10 + 1; // for terminating null character in string, not needed

blackjack_game_move_t getMoveFromMatrix(blackjack_game_move_t matrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE], card_t dealerCard, BlackjackHand playerHand);

// clang-format off
const blackjack_game_move_t perfect_algorithm_matrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE] = {
// Hard 5-20          Soft A2-A9 Pair 22-AA      Dealer's face up card
  "hhhhhddhssssssss" "hhhhhdss" "pphdppppsp", // 2
  "hhhhdddhssssssss" "hhhhddss" "pphdppppsp", // 3
  "hhhhdddsssssssss" "hhddddss" "pphdppppsp", // 4
  "hhhhdddsssssssss" "ddddddss" "pppdppppsp", // 5
  "hhhhdddsssssssss" "ddddddds" "pppdppppsp", // 6
  "hhhhhddhhhhhssss" "hhhhhsss" "pphdhppssp", // 7
  "hhhhhddhhhhhssss" "hhhhhsss" "hhhdhhppsp", // 8
  "hhhhhddhhhhhssss" "hhhhhhss" "hhhdhhppsp", // 9
  "hhhhhhdhhhhhssss" "hhhhhhss" "hhhhhhpssp", // T
  "hhhhhhdhhhhhssss" "hhhhhhss" "hhhhhhpssp"  // A
};
// clang-format on

#endif //BLACKJACKSTATS_ALGORITHM_H
