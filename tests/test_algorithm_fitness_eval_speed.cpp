#include "../src/Blackjack/Game/BlackjackGame.h"
#include "../src/algorithm.h"
#include "test_helpers.h"
#include <chrono>
#include <cstdio>

const uint32_t FITNESS_GAME_SIMS = 10000;

int8_t simulateGame(uint32_t seed, blackjack_game_move_t algorithmMatrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE]) {
  auto game = BlackjackGame(seed);

  if (game.gameState() == BLACKJACK_GAME_STATE_PLAYER_FINISHED) {
    return 1;
  }

  const card_t faceUp = game.dealerHand.getCardFromTop();

  while (game.gameState() == BLACKJACK_GAME_STATE_IN_PROGRESS) {
    int8_t nextHandIndex = game.player.getNextHandIndex();
    blackjack_game_move_t move = getMoveFromMatrix(algorithmMatrix, faceUp, *game.player.hands[nextHandIndex]);
    switch (move) {
      default:
      case BLACKJACK_GAME_MOVE_STAND: {
        game.player.stand(nextHandIndex);
        break;
      }
      case BLACKJACK_GAME_MOVE_HIT: {
        game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), false);
        break;
      }
      case BLACKJACK_GAME_MOVE_DOUBLE_DOWN: {
        game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), true);
        break;
      }
      case BLACKJACK_GAME_MOVE_SPLIT: {
        if (game.player.hands[nextHandIndex]->canSplit()) {
          game.player.splitHand(nextHandIndex);
        } else {
          game.player.stand(nextHandIndex);
        }
      }
    }
  }

  game.dealerHits();

  return game.moneyFlow();
}

int32_t fitness(blackjack_game_move_t algorithmMatrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE]) {
  //  printf("Running fitness test on algorithm matrix\n");
  int32_t moneyFlow = 0;
  for (uint32_t seed = 0; seed < FITNESS_GAME_SIMS; seed++) {
    moneyFlow += simulateGame(seed, algorithmMatrix);
    //    if (seed % 1000 == 0) {
    //      printf("%.2f%% finished\n", std::round(((float) seed / FITNESS_GAME_SIMS) * 100));
    //    }
  }
  //  printf("Fitness: %d\n", moneyFlow);
  return moneyFlow;
}

int main() {
  TEST_START("blackjack algorithm fitness evaluation speed")

  TEST_LOG("Testing scoring speed\n") {
    auto start = std::chrono::high_resolution_clock::now();
    fitness(perfect_algorithm_matrix);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    float average = (float) duration / FITNESS_GAME_SIMS;
    TEST_LOG("Took %lld ms to score algorithm matrix with %d games (%f ms per game)\n", duration, FITNESS_GAME_SIMS, average)
    TEST_ASSERT_LESS_THAN_OR_EQUAL_TO_INT(duration, 2000)
  }

  TEST_END()

  return 0;
}
