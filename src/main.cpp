#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include <cstdio>
#include <random>

int8_t simulateGame(uint32_t seed, card_t &sum) {
  printf("Blackjack game (#%d)\n", seed);
  auto game = BlackjackGame(seed);

  game.player.printHands();

  sum = game.player.hands[0]->getHandValue();

  if (game.gameState() == BLACKJACK_GAME_STATE_PLAYER_FINISHED) {
    printf("Player wins with instant blackjack!\n");
    return 1;
  }

  printf("\nDealer hand: ");
  printCard(game.dealerHand.getCardFromTop());
  printf("??  \n");

  std::mt19937 rng(seed);
  std::uniform_int_distribution<uint8_t> dist(0, 1);

  while (game.gameState() == BLACKJACK_GAME_STATE_IN_PROGRESS) {
    int8_t nextHandIndex = game.player.getNextHandIndex();
    if (game.player.hands[nextHandIndex]->canSplit()) {
      printf("Split hand %d\n", nextHandIndex + 1);
      game.player.splitHand(nextHandIndex);
      game.player.printHands();
      printf("\n");
    }
    if (dist(rng) == 1) {
      bool doubleDown = !game.player.handsDoubledDown[nextHandIndex] ? dist(rng) == 1 : false;
      if (doubleDown) {
        printf("Double down hand %d\n", nextHandIndex + 1);
      } else {
        printf("Hit hand %d\n", nextHandIndex + 1);
      }
      game.player.hit(nextHandIndex, game.deck.drawCardFromTop(), doubleDown);
      game.player.printHands();
      printf("\n");
    } else {
      printf("Stand on hand %d\n", nextHandIndex + 1);
      game.player.stand(nextHandIndex);
    }
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
  printf("seed, sum, result\n");

  card_t sum;
  int8_t result;

  // result = simulateGame(0, sum);  // -2
  result = simulateGame(45, sum);  // +1
  // result = simulateGame(27, sum);  // 2 split +2
  // result = simulateGame(28, sum); // 4 split +4
  // result = simulateGame(80, sum);  // 2 split +4
  return 0;

  for (uint32_t seed = 0; seed < 1; seed++) {
    result = simulateGame(seed, sum);
    // printf("%d, %d, %s\n", seed, sum, result == BLACKJACK_GAME_PLAYER_WIN ? "WIN" : result == BLACKJACK_GAME_PLAYER_LOSS ? "LOSS"
    //                                                                                                                      : "TIE");
  }
}
