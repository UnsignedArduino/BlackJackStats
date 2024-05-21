#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include <cstdio>
#include <random>

//#define DEBUG

#ifdef DEBUG
  #define logf(...) printf(__VA_ARGS__);
#else
  #define logf(...)
#endif

const uint8_t ACTION_HIT = 1;
const uint8_t ACTION_STAND = 0;

const int8_t RESULT_WIN = 1;
const int8_t RESULT_LOSS = -1;
const int8_t RESULT_TIE = 0;

blackjack_game_state_t simulateGame(uint32_t seed, uint8_t action, card_t &sum) {
  logf("Blackjack game (#%d)\n", seed);
  BlackjackGame game;
  game.setup(seed);

  logf("Player hand: ");
#ifdef DEBUG
  game.playerHand.printHand();
#endif

  sum = game.playerHand.getHandValue();

  if (game.gameState() == BLACKJACK_GAME_PLAYER_WIN) {
    logf("Player wins with instant blackjack!\n");
    return BLACKJACK_GAME_PLAYER_WIN;
  }

  logf("\nDealer hand: ");
#ifdef DEBUG
  printCard(game.dealerHand.getCardFromTop());
#endif
  logf("??  \n");

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
  if (action == ACTION_HIT) {
    logf("Hit\n");
    game.playerHit();
    logf("Player hand: ");
#ifdef DEBUG
    game.playerHand.printHand();
#endif
    logf("\n");
  } else {
    logf("Stand\n");
    game.playerStand();
  }
#pragma clang diagnostic pop

  std::mt19937 rng(seed);
  std::uniform_int_distribution<uint8_t> dist(0, 1);

  while (game.gameState() == BLACKJACK_GAME_IN_PROGRESS) {
    if (dist(rng) == ACTION_HIT) {
      logf("Hit\n");
      game.playerHit();
      logf("Player hand: ");
#ifdef DEBUG
      game.playerHand.printHand();
#endif
      logf("\n");
    } else {
      logf("Stand\n");
      break;
    }
  }
  game.playerStand();

  logf("Dealer hand: ");
#ifdef DEBUG
  game.dealerHand.printHand();
#endif
  logf("\n");

#ifdef DEBUG
  switch (game.gameState()) {
    case BLACKJACK_GAME_PLAYER_WIN:
      logf("Player wins!\n");
      break;
    case BLACKJACK_GAME_PLAYER_LOSS:
      logf("Dealer wins!\n");
      break;
    case BLACKJACK_GAME_DRAW:
      logf("Draw!\n");
      break;
    default:
      break;
  }
#endif

  return game.gameState();
}

int main() {
  printf("seed, sum, action, result\n");

  card_t sum;
  blackjack_game_state_t result;
  for (uint32_t seed = 0; seed < 10000; seed++) {
    result = simulateGame(seed, ACTION_STAND, sum);
    printf("%d, %d, STAND, %s\n", seed, sum, result == BLACKJACK_GAME_PLAYER_WIN ? "WIN" : result == BLACKJACK_GAME_PLAYER_LOSS ? "LOSS"
                                                                                                                                : "TIE");
    result = simulateGame(seed, ACTION_HIT, sum);
    printf("%d, %d, HIT, %s\n", seed, sum, result == BLACKJACK_GAME_PLAYER_WIN ? "WIN" : result == BLACKJACK_GAME_PLAYER_LOSS ? "LOSS"
                                                                                                                              : "TIE");
  }
}
