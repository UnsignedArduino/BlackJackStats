#include <cstdint>

#ifndef BLACKJACKSTATS_CARDS_H
  #define BLACKJACKSTATS_CARDS_H

typedef uint8_t card_t;

const card_t CARD_NULL = 0;

const card_t CARD_VALUE_MASK = 0b001111;

const card_t CARD_VALUE_ACE = 1;
const card_t CARD_VALUE_TWO = 2;
const card_t CARD_VALUE_THREE = 3;
const card_t CARD_VALUE_FOUR = 4;
const card_t CARD_VALUE_FIVE = 5;
const card_t CARD_VALUE_SIX = 6;
const card_t CARD_VALUE_SEVEN = 7;
const card_t CARD_VALUE_EIGHT = 8;
const card_t CARD_VALUE_NINE = 9;
const card_t CARD_VALUE_TEN = 10;
const card_t CARD_VALUE_JACK = 11;
const card_t CARD_VALUE_QUEEN = 12;
const card_t CARD_VALUE_KING = 13;

const card_t CARD_SUIT_MASK = 0b110000;

const card_t CARD_SUIT_HEARTS_FLAG = 0b000000;
const card_t CARD_SUIT_DIAMONDS_FLAG = 0b010000;
const card_t CARD_SUIT_CLUBS_FLAG = 0b100000;
const card_t CARD_SUIT_SPADES_FLAG = 0b110000;

void printCard(card_t card);

#endif//BLACKJACKSTATS_CARDS_H
