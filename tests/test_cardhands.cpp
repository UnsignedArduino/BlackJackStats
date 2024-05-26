#include "../src/Cards/Hand/CardHand.h"
#include "test_helpers.h"
#include <cstdio>

int main() {
  TEST_START("card hands")

  TEST_LOG("Creating hand\n")
  CardHand hand = CardHand();
  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 0)

  TEST_LOG("Filling hand with deck\n")
  hand.fillHandWithDeck();
  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 52)

  TEST_LOG("Clearing hand\n")
  hand.clearHand();
  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 0)

  TEST_LOG("Printing hand\n")
  hand.printHand();

  TEST_ASSERT_EQUAL_TO_CARD(hand.getCardFromTop(), CARD_NULL)
  TEST_ASSERT_EQUAL_TO_CARD(hand.getCardFromBottom(), CARD_NULL)
  TEST_ASSERT_EQUAL_TO_CARD(hand.getCard(16), CARD_NULL)

  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCardFromTop(), CARD_NULL)
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCardFromBottom(), CARD_NULL)
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCard(16), CARD_NULL)

  TEST_LOG("Adding cards\n")
  hand.addCardToBottom(CARD_SUIT_CLUBS_FLAG | CARD_RANK_THREE);
  hand.insertCard(CARD_SUIT_SPADES_FLAG | CARD_RANK_FOUR, 1);
  hand.addCardToTop(CARD_SUIT_DIAMONDS_FLAG | CARD_RANK_TWO);
  hand.addCardToTop(CARD_SUIT_HEARTS_FLAG | CARD_RANK_ACE);

  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 4)
  TEST_ASSERT_EQUAL_TO_CARD(hand.getCardFromTop(), CARD_SUIT_HEARTS_FLAG | CARD_RANK_ACE)
  TEST_ASSERT_EQUAL_TO_CARD(hand.getCardFromBottom(), CARD_SUIT_SPADES_FLAG | CARD_RANK_FOUR)
  TEST_ASSERT_EQUAL_TO_CARD(hand.getCard(1), CARD_SUIT_DIAMONDS_FLAG | CARD_RANK_TWO)

  TEST_LOG("Drawing cards\n");
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCardFromTop(), CARD_SUIT_HEARTS_FLAG | CARD_RANK_ACE)
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCardFromBottom(), CARD_SUIT_SPADES_FLAG | CARD_RANK_FOUR)
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCard(1), CARD_SUIT_CLUBS_FLAG | CARD_RANK_THREE)
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCard(0), CARD_SUIT_DIAMONDS_FLAG | CARD_RANK_TWO)
  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 0)

  TEST_LOG("Filling hand with deck\n");
  hand.fillHandWithDeck();

  TEST_LOG("Drawing cards\n")
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCard(0), CARD_SUIT_HEARTS_FLAG | CARD_RANK_ACE)
  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 51)
  TEST_ASSERT_EQUAL_TO_CARD(hand.drawCard(50), CARD_SUIT_SPADES_FLAG | CARD_RANK_KING)
  TEST_ASSERT_EQUAL_TO_INT(hand.getHandSize(), 50)

  TEST_END()

  return 0;
}
