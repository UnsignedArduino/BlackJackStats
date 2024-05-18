#include "helpers.h"
#include <cstdio>

bool assert(bool condition, const char *test, uint32_t number) {
  printf("| |- Test %d: %s", number, test);
  if (condition) {
    printf("...pass!\n");
  } else {
    printf("...fail!\n");
  }
  return condition;
}
