#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include "algorithm.h"
#include <cstdio>
#include <random>

int8_t simulateGame(uint32_t seed, blackjack_game_move_t algorithmMatrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE]) {
  printf("Blackjack game (#%d)\n", seed);
  auto game = BlackjackGame(seed);

  game.player.printHands();

  if (game.gameState() == BLACKJACK_GAME_STATE_PLAYER_FINISHED) {
    printf("\nPlayer wins with instant blackjack!\n");
    printf("Hand 1: WIN (+1)\n");
    return 1;
  }

  printf("\nDealer hand: ");
  const card_t faceUp = game.dealerHand.getCardFromTop();
  printCard(faceUp);
  printf("??  \n");

  while (game.gameState() == BLACKJACK_GAME_STATE_IN_PROGRESS) {
    int8_t nextHandIndex = game.player.getNextHandIndex();
    blackjack_game_move_t move = getMoveFromMatrix(algorithmMatrix, faceUp, *game.player.hands[nextHandIndex]);
    switch (move) {
      default:
      case BLACKJACK_GAME_MOVE_STAND: {
        printf("Stand on hand %d\n", nextHandIndex + 1);
        game.player.stand(nextHandIndex);
        break;
      }
      case BLACKJACK_GAME_MOVE_HIT: {
        printf("Hit hand %d\n", nextHandIndex + 1);
        game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), false);
        break;
      }
      case BLACKJACK_GAME_MOVE_DOUBLE_DOWN: {
        printf("Double down hand %d\n", nextHandIndex + 1);
        game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), true);
        break;
      }
      case BLACKJACK_GAME_MOVE_SPLIT: {
        if (game.player.hands[nextHandIndex]->canSplit()) {
          printf("Split hand %d\n", nextHandIndex + 1);
          game.player.splitHand(nextHandIndex);
        } else {
          printf("Warning: illegal attempt to split hand %d\n", nextHandIndex + 1);
          printf("Stand on hand %d\n", nextHandIndex + 1);
          game.player.stand(nextHandIndex);
        }
      }
    }
    game.player.printHands();
    printf("\n");
  }

  printf("Dealer hand: ");
  game.dealerHand.printHand();
  printf("\n");

  game.dealerHits();

  printf("Dealer hand after drawings: ");
  game.dealerHand.printHand();
  printf("\n");

  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (game.player.hands[i] == nullptr) {
      continue;
    }
    int8_t resultOfHand = game.moneyFlow(i);
    if (resultOfHand > 0) {
      printf("Hand %d: WIN (%+d)\n", i + 1, game.player.handsDoubledDown[i] ? 2 : 1);
    } else if (resultOfHand < 0) {
      printf("Hand %d: LOSS (%+d)\n", i + 1, game.player.handsDoubledDown[i] ? -2 : -1);
    } else {
      printf("Hand %d: DRAW (+0)\n", i + 1);
    }
  }

  printf("Total money flow: %+d\n", game.moneyFlow());

  return game.moneyFlow();
}

int main() {
  printf("seed, perfect_algorithm_matrix, result\n");

  int8_t result;

  //  result = simulateGame(0, perfect_algorithm_matrix); // +1 with ace
  //  result = simulateGame(1, perfect_algorithm_matrix); // -1
  result = simulateGame(2, perfect_algorithm_matrix);
  //  result = simulateGame(10, perfect_algorithm_matrix); // +1 instant blackjack
  //  result = simulateGame(45, perfect_algorithm_matrix); // -1
  //  result = simulateGame(27, perfect_algorithm_matrix);// 2 split +2
  //  result = simulateGame(28, perfect_algorithm_matrix);// 4 split +4
  //  result = simulateGame(80, perfect_algorithm_matrix);// 2 split +4

  //  for (uint32_t seed = 0; seed < 1; seed++) {
  //    result = simulateGame(seed, perfect_algorithm_matrix);
  //    // printf("%d, %d, %s\n", seed, perfect_algorithm_matrix, result == BLACKJACK_GAME_PLAYER_WIN ? "WIN" : result == BLACKJACK_GAME_PLAYER_LOSS ? "LOSS"
  //    //                                                                                                                      : "TIE");
  //  }
}
