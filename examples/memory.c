#include "chest.h"

CHEST_TEST(memory_assertions) {
  int x = 42, y = 42;
  CHEST_EQUAL(c, x, y);
  int arr1[] = {1, 2, 3};
  int arr2[] = {1, 2, 3};
  CHEST_EQUAL(c, arr1, arr2);
}

RUN_ALL(CHEST_ADD(c, memory_assertions););
