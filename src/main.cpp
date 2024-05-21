#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include <cstdio>
#include <random>

int main() {
  const uint32_t seed = 0;

  printf("Blackjack game (#%d)\n", seed);
  BlackjackGame game;
  game.setup(seed);

  printf("Player hand: ");
  game.playerHand.printHand();

  printf("\nDealer hand: ");
  printCard(game.dealerHand.getCardFromTop());
  printf("??  \n");

  while (game.gameState() == BLACKJACK_GAME_IN_PROGRESS) {
    printf("Hit or stand? (h/s):");
    char input;
    scanf("%c", &input);

    if (input == 'h') {
      game.playerHit();
      printf("Player hand: ");
      game.playerHand.printHand();
      printf("\n");
    } else if (input == 's') {
      break;
    }
  }
  game.playerStand();

  printf("Dealer hand: ");
  game.dealerHand.printHand();
  printf("\n");

  switch (game.gameState()) {
    case BLACKJACK_GAME_PLAYER_WIN:
      printf("Player wins!\n");
      break;
    case BLACKJACK_GAME_PLAYER_LOSS:
      printf("Dealer wins!\n");
      break;
    case BLACKJACK_GAME_DRAW:
      printf("Draw!\n");
      break;
    default:
      break;
  }

  return 0;
}
