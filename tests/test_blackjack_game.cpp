#include "../src/Blackjack/Game/BlackjackGame.h"
#include "../src/algorithm.h"
#include "test_helpers.h"
#include <cstdio>

int8_t simulateGame(uint32_t seed) {
  //  TEST_LOG("Blackjack game (#%d)\n", seed);
  auto game = BlackjackGame(seed);

  //  game.player.printHands();

  //  sum = game.player.hands[0]->getSoftHandValue();

  if (game.gameState() == BLACKJACK_GAME_STATE_PLAYER_FINISHED) {
    //    TEST_LOG("Player wins with instant blackjack!\n");
    return 1;
  }

  //  TEST_LOG("\nDealer hand: ");
  const card_t faceUp = game.dealerHand.getCardFromTop();
  //  printCard(faceUp);
  //  TEST_LOG("??  \n");

  while (game.gameState() == BLACKJACK_GAME_STATE_IN_PROGRESS) {
    int8_t nextHandIndex = game.player.getNextHandIndex();
    blackjack_game_move_t move = getMoveFromMatrix(perfect_algorithm_matrix, faceUp, *game.player.hands[nextHandIndex]);
    switch (move) {
      default:
      case BLACKJACK_GAME_MOVE_STAND: {
        //        TEST_LOG("Stand on hand %d\n", nextHandIndex + 1);
        game.player.stand(nextHandIndex);
        break;
      }
      case BLACKJACK_GAME_MOVE_HIT: {
        //        TEST_LOG("Hit hand %d\n", nextHandIndex + 1);
        game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), false);
        break;
      }
      case BLACKJACK_GAME_MOVE_DOUBLE_DOWN: {
        //        TEST_LOG("Double down hand %d\n", nextHandIndex + 1);
        game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), true);
        break;
      }
      case BLACKJACK_GAME_MOVE_SPLIT: {
        if (game.player.hands[nextHandIndex]->canSplit()) {
          //          TEST_LOG("Split hand %d\n", nextHandIndex + 1);
          game.player.splitHand(nextHandIndex);
        } else {
          //          TEST_LOG("Warning: illegal attempt to split hand %d\n", nextHandIndex + 1);
          //          TEST_LOG("Stand on hand %d\n", nextHandIndex + 1);
          game.player.stand(nextHandIndex);
        }
      }
    }
    //    game.player.printHands();
    //    TEST_LOG("\n");
  }

  //  TEST_LOG("Dealer hand: ");
  //  game.dealerHand.printHand();
  //  TEST_LOG("\n");

  game.dealerHits();

  //  TEST_LOG("Dealer hand after drawings: ");
  //  game.dealerHand.printHand();
  //  TEST_LOG("\n");

  //  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
  //    if (game.player.hands[i] == nullptr) {
  //      continue;
  //    }
  //    int8_t resultOfHand = game.moneyFlow(i);
  //    if (resultOfHand > 0) {
  //      TEST_LOG("Hand %d: WIN (%+d)\n", i + 1, game.player.handsDoubledDown[i] ? 2 : 1);
  //    } else if (resultOfHand < 0) {
  //      TEST_LOG("Hand %d: LOSS (%+d)\n", i + 1, game.player.handsDoubledDown[i] ? -2 : -1);
  //    } else {
  //      TEST_LOG("Hand %d: DRAW (+0)\n", i + 1);
  //    }
  //  }

  //  TEST_LOG("Total money flow: %+d\n", game.moneyFlow());

  return game.moneyFlow();
}

// Index is seed
const int8_t gameResults[] = {1, -1, -1, -1, 0, -1, -1, -1, -1, 1, 1, -1, -2, 2, -1, -1, 2, 0, -1, -1, 1, -1, 2, 0, 1, -1, -1, 1, 1, -1, -1, -1, 2, -1, 1, 0, 1, -2, -1, -1, -1, -1, 0, 1, -1, -1, 1, -1, 1, -1, 1, 1, 2, -1, 0, 1, -1, -1, -1, -1, -1, 0, 1, -1, -1, -2, -1, 1, 1, 1, -1, 0, 2, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, 2, 1, -1, -1, 1, -1, 1, 2, -1, 0, -1, -1, 1, 1, 1, -1};

int main() {
  TEST_START("blackjack games")

  TEST_LOG("Simulating blackjack games\n")

  //  printf("{");
  for (uint8_t i = 0; i < 100; i++) {
    TEST_ASSERT_EQUAL_TO_INT(simulateGame(i), gameResults[i]);
    //    printf("%d, ", simulateGame(i));
  }
  //  printf("}\n");

  float winRate = 0;
  const uint32_t times = 10000;
  TEST_LOG("Testing win rate with perfect algorithm for %d games\n", times)
  for (uint32_t i = 0; i < times; i++) {
    if (simulateGame(i) > 0) {
      winRate++;
    }
    if (i % 1000 == 0) {
      TEST_LOG("%f%% done\n", (float) i / times * 100)
    }
  }
  winRate /= times;
  TEST_LOG("Win rate: %f\n", winRate)
  TEST_ASSERT_LESS_THAN_OR_EQUAL_TO_INT(winRate, 0.5)

  TEST_END()

  return 0;
}
