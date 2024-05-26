#include "Blackjack/Game/BlackjackGame.h"
#include "Cards/Hand/CardHand.h"
#include "algorithm.h"
#include <cmath>
#include <cstdio>
#include <random>
#include <time.h>

const uint32_t FITNESS_GAME_SIMS = 1000;

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

float randFloat(){
  return (float)(rand()) / (float)(RAND_MAX);
}

void mutate(blackjack_game_move_t (&matrix)[AM_DEALERS_SIZE][AM_PLAYERS_SIZE], float rate){
  for (int y=0;y<AM_DEALERS_SIZE;y++){
    for (int x=0;x<AM_PLAYERS_SIZE-1;x++){
      if (randFloat() < rate){
        float choice = randFloat();
        if (choice < 0.25)
          matrix[y][x] = 's';
        else if (choice < 0.5)
          matrix[y][x] = 'h';
        else if (choice < 0.75)
          matrix[y][x] = 'p';
        else
          matrix[y][x] = 'd';
      }
    }
  }
}

void crossover(blackjack_game_move_t (&parentA)[AM_DEALERS_SIZE][AM_PLAYERS_SIZE], 
              blackjack_game_move_t (&parentB)[AM_DEALERS_SIZE][AM_PLAYERS_SIZE],
              blackjack_game_move_t (&child)[AM_DEALERS_SIZE][AM_PLAYERS_SIZE]){
  for (int y=0;y<AM_DEALERS_SIZE;y++){
    for (int x=0;x<AM_PLAYERS_SIZE-1;x++){
      if (randFloat() < 0.5)
        child[y][x] = parentA[y][x];
      else
        child[y][x] = parentB[y][x];
    }
  }
}

void copyAIntoB(blackjack_game_move_t (&matrixA)[AM_DEALERS_SIZE][AM_PLAYERS_SIZE], blackjack_game_move_t (&matrixB)[AM_DEALERS_SIZE][AM_PLAYERS_SIZE]){
  for (int y=0;y<AM_DEALERS_SIZE;y++){
    for (int x=0;x<AM_PLAYERS_SIZE-1;x++){
      matrixB[y][x] = matrixA[y][x];
    }
  }
}
int main() {
  srand(time(0));

  blackjack_game_move_t base[AM_DEALERS_SIZE][AM_PLAYERS_SIZE] = {
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // A
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 2
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 3
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 4
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 5
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 6
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 7
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 8
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh", // 9
    "hhhhhhhhhhhhhhhh" "hhhhhhhh" "hhhhhhhhhh"  // T
  };

  const int POPSIZE = 100;
  const int BREEDINGSIZE = 5;
  blackjack_game_move_t population[POPSIZE][AM_DEALERS_SIZE][AM_PLAYERS_SIZE] = {};
  int population_fitness[POPSIZE] = {};

  // Randomised Population
  for (int i=0;i<POPSIZE;i++){
    copyAIntoB(base, population[i]);
    mutate(population[i], 1);
  }

  // Get fitness
  for (int gen=0;gen<10000;gen++){
    int totalFitness = 0;
    int bestFitness = -1000000000;
    int bestIndex = 0;
    printf("Generation: %d\n", gen);
    printf("Calculating Fitness:\n");
    for (int i=0;i<POPSIZE;i++){
      population_fitness[i] = fitness(population[i]);
      if (population_fitness[i] > bestFitness){
        bestFitness = population_fitness[i];
        bestIndex = i;
      }
      totalFitness += population_fitness[i];
      if (i % 25 == 0)
        printf("Simulating: %d ", i);
    }
    printf("\n");
    printf("Best Fitness: %d, Average Fitness: %.3f\n", bestFitness, (float)(totalFitness)/POPSIZE);
    printf("Best Stratgey:\n");
    for (int i=0;i<AM_DEALERS_SIZE;i++){
      printf(population[bestIndex][i]);
      printf("\n");
    }
    // Roulette Selection of breeding pool
    blackjack_game_move_t pool[BREEDINGSIZE][AM_DEALERS_SIZE][AM_PLAYERS_SIZE] = {};
    int selected = 0;
    while (selected < BREEDINGSIZE){
      for (int i=0;i<POPSIZE;i++){
        if (randFloat() < (float)population_fitness[i]/totalFitness){
          copyAIntoB(population[i], pool[selected]);
          selected++;
          break;
        }
      }
    }

    // Repopulate
    copyAIntoB(population[bestIndex], population[0]);
    for (int i=0;i<POPSIZE;i++){
      crossover(pool[(int)(randFloat()*BREEDINGSIZE)], pool[(int)(randFloat()*BREEDINGSIZE)], population[i]);
      mutate(population[i], 0.12);
    }
    printf("\n");
  }
  

}
