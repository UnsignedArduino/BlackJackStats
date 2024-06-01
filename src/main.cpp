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

const uint8_t ACTION_HIT = 1;
const uint8_t ACTION_STAND = 0;

const int8_t RESULT_WIN = 1;
const int8_t RESULT_LOSS = -1;
const int8_t RESULT_TIE = 0;

int TABLE[12][2] = {};


void simulateStand(uint32_t seed){
  BlackjackGame game(seed);
  //printf("Player hand: ");
  //game.playerHand.printHand();
  //printf("\n");

  // printf("Dealer hand: ");
  // game.dealerHand.printHand();
  // printf("\n");

  game.dealerHits();

  // printf("Player Stand\nDealer hand: ");
  // game.dealerHand.printHand();
  // printf("\n");

  int tableIndex = game.dealerHand.hand[0] & CARD_RANK_MASK;
  //printf("CARD %d\n", tableIndex);
  if (tableIndex >= 10){
    tableIndex = 10;
  }
  if (game.dealerHand.getSoftHandValue() > 21 && game.dealerHand.getHardHandValue() > 21){
    TABLE[tableIndex][0]++;
  }
  else {
    //printf("Dealer did not bust\n");
    TABLE[tableIndex][1]++;
  }
  //printf("\n");
}

void calculateBustRates(int total){
  int TOTAL_WINS = 0;

  for (uint32_t seed=0;seed<total;seed++){
    simulateStand(seed);
    if (seed % 10000 == 0)
      printf("Simulated %d games\n", seed);
  }
  printf("Simulated %d hands\n", total);
  for (int i=1;i<11;i++){
    int N = (TABLE[i][0]+TABLE[i][1]);
    float prop = (float)TABLE[i][0]/(float)N;
    float ME = 1.96f*sqrt(prop*(1-prop)/N);
    printf("Dealer Face Up: %d, Bust/Total: %d/%d, Bust Rate:%.3f+-%.3f, Interval: [%.3f, %.3f] (95%%)\n", i, TABLE[i][0], N, 
      prop, ME, prop-ME, prop+ME);
    TOTAL_WINS += TABLE[i][0];
  }
  float prop_ = (float)TOTAL_WINS/(float)total;
  float ME_ = 1.96f*sqrt(prop_*(1-prop_)/total);
  printf("Bust/Total: %d/%d, Bust Rate:%.3f+-%.3f, Interval: [%.3f, %.3f] (95%%)\n", 
    TOTAL_WINS, total, prop_, ME_, prop_-ME_, prop_+ME_);
}
int main() {
  srand(time(NULL));
  calculateBustRates(100000);
  
  
  return 0;
}
