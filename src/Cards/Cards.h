#include <cstdint>

#ifndef BLACKJACKSTATS_CARDS_H
  #define BLACKJACKSTATS_CARDS_H

typedef uint8_t card_t;

const card_t CARD_NULL = 0;

const card_t CARD_RANK_MASK = 0b001111;

const card_t CARD_RANK_ACE = 1;
const card_t CARD_RANK_TWO = 2;
const card_t CARD_RANK_THREE = 3;
const card_t CARD_RANK_FOUR = 4;
const card_t CARD_RANK_FIVE = 5;
const card_t CARD_RANK_SIX = 6;
const card_t CARD_RANK_SEVEN = 7;
const card_t CARD_RANK_EIGHT = 8;
const card_t CARD_RANK_NINE = 9;
const card_t CARD_RANK_TEN = 10;
const card_t CARD_RANK_JACK = 11;
const card_t CARD_RANK_QUEEN = 12;
const card_t CARD_RANK_KING = 13;

const card_t CARD_RANKS[13] = {
  CARD_RANK_ACE,
  CARD_RANK_TWO,
  CARD_RANK_THREE,
  CARD_RANK_FOUR,
  CARD_RANK_FIVE,
  CARD_RANK_SIX,
  CARD_RANK_SEVEN,
  CARD_RANK_EIGHT,
  CARD_RANK_NINE,
  CARD_RANK_TEN,
  CARD_RANK_JACK,
  CARD_RANK_QUEEN,
  CARD_RANK_KING};

const card_t CARD_SUIT_MASK = 0b110000;

const card_t CARD_SUIT_HEARTS_FLAG = 0b000000;
const card_t CARD_SUIT_DIAMONDS_FLAG = 0b010000;
const card_t CARD_SUIT_CLUBS_FLAG = 0b100000;
const card_t CARD_SUIT_SPADES_FLAG = 0b110000;

const card_t CARD_SUITS[4] = {
  CARD_SUIT_HEARTS_FLAG,
  CARD_SUIT_DIAMONDS_FLAG,
  CARD_SUIT_CLUBS_FLAG,
  CARD_SUIT_SPADES_FLAG};

void printCard(card_t card);

#endif//BLACKJACKSTATS_CARDS_H
