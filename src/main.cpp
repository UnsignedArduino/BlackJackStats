#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include <cstdio>
#include <random>

int8_t simulateGame(uint32_t seed, card_t &sum) {
  printf("Blackjack game (#%d)\n", seed);
  BlackjackGame game = BlackjackGame(seed);

  game.player.printHands();

  // sum = game.playerHand.getHandValue();

  // if (game.gameState() == BLACKJACK_GAME_PLAYER_WIN) {
  //   printf("Player wins with instant blackjack!\n");
  //   return BLACKJACK_GAME_PLAYER_WIN;
  // }

  // printf("\nDealer hand: ");
  // printCard(game.dealerHand.getCardFromTop());
  // printf("??  \n");

  // std::mt19937 rng(seed);
  // std::uniform_int_distribution<uint8_t> dist(0, 1);

  // while (game.gameState() == BLACKJACK_GAME_IN_PROGRESS) {
  //   if (dist(rng) == 1) {
  //     printf("Hit\n");
  //     game.playerHit();
  //     printf("Player hand: ");
  //     game.playerHand.printHand();
  //     printf("\n");
  //   } else {
  //     printf("Stand\n");
  //     break;
  //   }
  // }
  // game.playerStand();

  // printf("Dealer hand: ");
  // game.dealerHand.printHand();
  // printf("\n");

  // switch (game.gameState()) {
  //   case BLACKJACK_GAME_PLAYER_WIN:
  //     printf("Player wins!\n");
  //     break;
  //   case BLACKJACK_GAME_PLAYER_LOSS:
  //     printf("Dealer wins!\n");
  //     break;
  //   case BLACKJACK_GAME_DRAW:
  //     printf("Draw!\n");
  //     break;
  //   default:
  //     break;
  // }

  // return game.gameState();
}

int main() {
  printf("seed, sum, result\n");

  card_t sum;
  int8_t result;
  for (uint32_t seed = 0; seed < 1; seed++) {
    result = simulateGame(seed, sum);
    // printf("%d, %d, %s\n", seed, sum, result == BLACKJACK_GAME_PLAYER_WIN ? "WIN" : result == BLACKJACK_GAME_PLAYER_LOSS ? "LOSS"
    //                                                                                                                      : "TIE");
  }
}
