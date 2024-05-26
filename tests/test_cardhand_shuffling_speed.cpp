#include "../src/Cards/Hand/CardHand.h"
#include "test_helpers.h"
#include <chrono>
#include <cstdio>

const uint32_t ITERATIONS = 10000;

int main() {
  TEST_START("card hand shuffling speed")

  TEST_LOG("Preparing hand\n")
  CardHand hand = CardHand();

  TEST_LOG("Testing %d clears, fills, and shuffles\n", ITERATIONS) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < ITERATIONS; i++) {
      hand.clearHand();
      hand.fillHandWithDeck();
      hand.shuffleHand(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    TEST_LOG("Took %lld ms for %d iterations\n", duration, ITERATIONS)
    float average = (float) duration / ITERATIONS;
    TEST_LOG("Average time per iteration: %f ms\n", average)
    TEST_ASSERT_LESS_THAN_OR_EQUAL_TO_INT(average * 10, 5)
  }

  TEST_LOG("Testing %d shuffles\n", ITERATIONS) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < ITERATIONS; i++) {
      hand.shuffleHand(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    TEST_LOG("Took %lld ms for %d iterations\n", duration, ITERATIONS)
    float average = (float) duration / ITERATIONS;
    TEST_LOG("Average time per iteration: %f ms\n", average)
    TEST_ASSERT_LESS_THAN_OR_EQUAL_TO_INT(average * 100, 5)
  }

  TEST_END()

  return 0;
}
