#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include "algorithm.h"
#include "helpers.h"
#include <cstdio>
#include <random>
#include <time.h>

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

int main() {
  
}
