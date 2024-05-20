#include <cstdint>

#ifndef BLACKJACKSTATS_HELPERS_H
  #define BLACKJACKSTATS_HELPERS_H

bool assert(bool condition, const char *test, uint32_t number);

  #define TEST_START(name)                 \
    {                                      \
      printf("|- Test suite: " name "\n"); \
      const char *test_name = name;        \
      uint32_t test_counter = 0;

  #define TEST_LOG(...) printf("> " __VA_ARGS__);

  #define TEST_ASSERT_TRUE(toRun)                             \
    {                                                         \
      bool actual = toRun;                                    \
      if (!assert(actual, #toRun " == true", test_counter)) { \
        printf("Expected: true\n");                           \
        printf("Got: false");                                 \
        TEST_END_FAIL()                                       \
        return 1;                                             \
      }                                                       \
    }                                                         \
    test_counter++;

  #define TEST_ASSERT_FALSE(toRun)                              \
    {                                                           \
      bool actual = toRun;                                      \
      if (!assert(!actual, #toRun " == false", test_counter)) { \
        printf("Expected: false\n");                            \
        printf("Got: true");                                    \
        TEST_END_FAIL()                                         \
        return 1;                                               \
      }                                                         \
    }                                                           \
    test_counter++;

  #define TEST_ASSERT_EQUAL_TO_INT(toRun, expected)                                    \
    {                                                                                  \
      int32_t actual = toRun;                                                          \
      if (!assert(actual == (expected), #toRun " == (" #expected ")", test_counter)) { \
        printf("Expected: ");                                                          \
        printf(#expected);                                                             \
        printf("\nGot: %d", actual);                                                   \
        TEST_END_FAIL()                                                                \
        return 1;                                                                      \
      }                                                                                \
    }                                                                                  \
    test_counter++;

  #define TEST_ASSERT_LESS_THAN_INT(toRun, expected)                                 \
    {                                                                                \
      int32_t actual = toRun;                                                        \
      if (!assert(actual < (expected), #toRun " < (" #expected ")", test_counter)) { \
        printf("Expected less than: ");                                              \
        printf(#expected);                                                           \
        printf("\nGot: %d", actual);                                                 \
        TEST_END_FAIL()                                                              \
        return 1;                                                                    \
      }                                                                              \
    }                                                                                \
    test_counter++;

  #define TEST_ASSERT_LESS_THAN_OR_EQUAL_TO_INT(toRun, expected)                       \
    {                                                                                  \
      int32_t actual = toRun;                                                          \
      if (!assert(actual <= (expected), #toRun " <= (" #expected ")", test_counter)) { \
        printf("Expected less than or equal to: ");                                    \
        printf(#expected);                                                             \
        printf("\nGot: %d", actual);                                                   \
        TEST_END_FAIL()                                                                \
        return 1;                                                                      \
      }                                                                                \
    }                                                                                  \
    test_counter++;

  #define TEST_ASSERT_GREATER_THAN_INT(toRun, expected)                              \
    {                                                                                \
      int32_t actual = toRun;                                                        \
      if (!assert(actual > (expected), #toRun " > (" #expected ")", test_counter)) { \
        printf("Expected greater than: ");                                           \
        printf(#expected);                                                           \
        printf("\nGot: %d", actual);                                                 \
        TEST_END_FAIL()                                                              \
        return 1;                                                                    \
      }                                                                              \
    }                                                                                \
    test_counter++;

  #define TEST_ASSERT_GREATER_THAN_OR_EQUAL_TO_INT(toRun, expected)                    \
    {                                                                                  \
      int32_t actual = toRun;                                                          \
      if (!assert(actual >= (expected), #toRun " >= (" #expected ")", test_counter)) { \
        printf("Expected greater than or equal to: ");                                 \
        printf(#expected);                                                             \
        printf("\nGot: %d", actual);                                                   \
        TEST_END_FAIL()                                                                \
        return 1;                                                                      \
      }                                                                                \
    }                                                                                  \
    test_counter++;

  #define TEST_ASSERT_EQUAL_TO_CARD(toRun, expected)                                   \
    {                                                                                  \
      card_t actual = toRun;                                                           \
      if (!assert(actual == (expected), #toRun " == (" #expected ")", test_counter)) { \
        printf("Expected: ");                                                          \
        printf(#expected);                                                             \
        printf("Got: ");                                                               \
        printCard(actual);                                                             \
        TEST_END_FAIL()                                                                \
        return 1;                                                                      \
      }                                                                                \
    }                                                                                  \
    test_counter++;

  #define TEST_END()                                                           \
    printf("|- Test suite: %s...%d tests passed!\n", test_name, test_counter); \
    }

  #define TEST_END_FAIL() printf("\n|- Test suite: %s...failed!\n", test_name);

#endif//BLACKJACKSTATS_HELPERS_H
