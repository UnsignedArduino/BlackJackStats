#include "../src/Blackjack/Game/BlackjackGame.h"
#include "helpers.h"
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
  //  printCard(game.dealerHand.getCardFromTop());
  //  TEST_LOG("??  \n");

  std::mt19937 rng(seed);
  std::uniform_int_distribution<uint8_t> dist(0, 1);

  while (game.gameState() == BLACKJACK_GAME_STATE_IN_PROGRESS) {
    int8_t nextHandIndex = game.player.getNextHandIndex();
    if (game.player.hands[nextHandIndex]->canSplit()) {
      //      TEST_LOG("Split hand %d\n", nextHandIndex + 1);
      game.player.splitHand(nextHandIndex);
      //      game.player.printHands();
      //      TEST_LOG("\n");
    }
    if (dist(rng) == 1) {
      bool doubleDown = !game.player.handsDoubledDown[nextHandIndex] ? dist(rng) == 1 : false;
      if (doubleDown) {
        //        TEST_LOG("Double down hand %d\n", nextHandIndex + 1);
      } else {
        //        TEST_LOG("Hit hand %d\n", nextHandIndex + 1);
      }
      game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), doubleDown);
      //      game.player.printHands();
      //      TEST_LOG("\n");
    } else {
      //      TEST_LOG("Stand on hand %d\n", nextHandIndex + 1);
      game.player.stand(nextHandIndex);
    }
  }

  //  TEST_LOG("Dealer hand: ");
  //  game.dealerHand.printHand();
  //  TEST_LOG("\n");

  game.dealerHits();

  //  TEST_LOG("Dealer hand after drawings: ");
  //  game.dealerHand.printHand();
  //  TEST_LOG("\n");

  for (uint8_t i = 0; i < PLAYER_SPLITS_MAX; i++) {
    if (game.player.hands[i] == nullptr) {
      continue;
    }
    int8_t resultOfHand = game.moneyFlow(i);
    if (resultOfHand > 0) {
      //      TEST_LOG("Hand %d: WIN (%+d)\n", i + 1, game.player.handsDoubledDown[i] ? 2 : 1);
    } else if (resultOfHand < 0) {
      //      TEST_LOG("Hand %d: LOSS (%+d)\n", i + 1, game.player.handsDoubledDown[i] ? -2 : -1);
    } else {
      //      TEST_LOG("Hand %d: DRAW (+0)\n", i + 1);
    }
  }

  //  TEST_LOG("Total money flow: %+d\n", game.moneyFlow());

  return game.moneyFlow();
}

// Index is seed
const int8_t gameResults[] = {-2, -1, -1, -2, -2, -1, 2, -1, -1, 1, 1, -1, -1, -2, 0, -2, -1, 0, -1, -1, -2, -1, -1, -2, -1, 2, 1, 2, 4, 2, -2, -1, 1, 1, 2, -1, 1, -1, -1, 2, -1, -1, 1, -1, -1, -1, -3, -1, 2, -1, -2, -1, 0, -2, -1, 1, -1, 1, -1, -2, -1, 0, 1, -1, -1, -1, -1, -2, -1, -1, 0, -1, 1, -1, -1, 1, -1, -1, -3, -1, 4, -1, -1, -1, 1, -2, -1, -2, -4, -1, 1, 1, -2, -2, -2, -1, 1, -2, 4, 2};

int main() {
  TEST_START("blackjack games")

  TEST_LOG("Simulating blackjack games\n")

  for (uint8_t i = 0; i < 100; i++) {
    TEST_ASSERT_EQUAL_TO_INT(simulateGame(i), gameResults[i]);
  }

  TEST_END()

  return 0;
}
