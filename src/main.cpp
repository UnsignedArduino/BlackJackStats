#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include <cstdio>
#include <random>

const uint32_t ITERATIONS = 1000;

const uint8_t HIT = 1;
const uint8_t STAND = 0;

void runOneRound(uint32_t seed, uint8_t action, uint32_t &wins, uint32_t &draws, uint32_t &losses) {
  wins = 0;
  draws = 0;
  losses = 0;

  printf("Starting Blackjack game with single player with deck ID %d\n", seed);
  BlackjackGame game;
  game.setup(seed);
  printf("Player hand: ");
  game.playerHand.printHand();
  printf("\n");

  if (game.checkGameResult() == WIN) {
    printf("Win!\n");
    printf("Ending game immediately\n");
    return;
  }

  printf("Dealer's first card: ");
  printCardAndValue(game.dealerHand.getCardFromTop());

  if (action == HIT) {
    printf("\nPlayer hits\n");
    game.hit();
    printf("Player hand: ");
    game.playerHand.printHand();
    printf("\n");
    if (game.checkGameResult() == WIN) {
      printf("Win!\n");
      wins = ITERATIONS;
      printf("Ending game immediately\n");
      return;
    } else if (game.checkGameResult() == LOSE) {
      printf("Lose!\n");
      losses = ITERATIONS;
      printf("Ending game immediately\n");
      return;
    }
  } else {
    printf("\nPlayer stands\n");
    game.stand();
    printf("Dealer hand: ");
    game.dealerHand.printHand();
    printf("\n");
    if (game.checkGameResult() == WIN) {
      printf("Win!\n");
      wins = ITERATIONS;
    } else if (game.checkGameResult() == DRAW) {
      printf("Draw!\n");
      draws = ITERATIONS;
    } else {
      printf("Lose!\n");
      losses = ITERATIONS;
    }
    printf("Ending game immediately\n");
    return;
  }

  printf("Simulating possible game outcomes\n");
  auto rng = std::mt19937(seed);
  std::uniform_int_distribution<uint8_t> dist(STAND, HIT);
  for (uint32_t i = 0; i < ITERATIONS; i++) {
    BlackjackGame gameCopy;
    gameCopy.setup(seed);
    gameCopy.hit();
    while (gameCopy.checkGameResult() == IN_PROGRESS) {
      if (dist(rng) == HIT) {
        gameCopy.hit();
      } else {
        gameCopy.stand();
      }
    }
    switch (gameCopy.checkGameResult()) {
      case WIN:
        wins++;
        break;
      case DRAW:
        draws++;
        break;
      case LOSE:
        losses++;
        break;
      default:
        break;
    }
  }
}

int main() {
  uint32_t wins, draws, losses;

  //  runOneRound(4, STAND, wins, draws, losses);// Wins
  //  printf("\n");
  //  runOneRound(0, STAND, wins, draws, losses);// Draws
  //  printf("\n");
  //  runOneRound(5, STAND, wins, draws, losses);// Loses
  //  printf("\n");

  printf("> Deck ID, Action, Wins, Draws, Losses\n");

  for (uint32_t i = 0; i < 10; i++) {
    runOneRound(i, STAND, wins, draws, losses);
    printf("W/D/L %d/%d/%d out of %d \n", wins, draws, losses, ITERATIONS);
    printf("> %d, STAND, %d, %d, %d\n", i, wins, draws, losses);
    runOneRound(i, HIT, wins, draws, losses);
    printf("W/D/L %d/%d/%d out of %d \n", wins, draws, losses, ITERATIONS);
    printf("> %d, HIT, %d, %d, %d\n", i, wins, draws, losses);
  }

  return 0;
}
