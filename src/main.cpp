#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include "algorithm.h"
#include <cmath>
#include <cstdio>
#include <random>

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

int64_t fitness(blackjack_game_move_t algorithmMatrix[AM_DEALERS_SIZE][AM_PLAYERS_SIZE]) {
  printf("Running fitness test on algorithm matrix\n");
  uint32_t wins = 0, draws = 0, losses = 0;
  int32_t moneyFlow = 0;
  for (uint32_t seed = 0; seed < FITNESS_GAME_SIMS; seed++) {
    int8_t result = simulateGame(seed, algorithmMatrix);
    moneyFlow += result;
    if (result > 0) {
      wins++;
    } else if (result < 0) {
      losses++;
    } else {
      draws++;
    }
    if (seed % 1000 == 0) {
      printf("%.2f%% finished\n", std::round(((float) seed / FITNESS_GAME_SIMS) * 100));
    }
  }
  int64_t fitness = wins * 2 + draws - losses + moneyFlow;
  printf("%d wins (%.2f%%, %d draws (%.2f%%), %d losses (%.2f%%)\n", wins, (float) wins / FITNESS_GAME_SIMS * 100, draws, (float) draws / FITNESS_GAME_SIMS * 100, losses, (float) losses / FITNESS_GAME_SIMS * 100);
  printf("Money flow: %d\n", moneyFlow);
  printf("Fitness: %lld\n", fitness);
  return fitness;
}

int main() {
  fitness(perfect_algorithm_matrix);
}
