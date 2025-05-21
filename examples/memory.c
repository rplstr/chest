#include "chest.h"

TEST(memory_assertions) {
  int x = 42, y = 42;
  memeq(c, x, y);
  int arr1[] = {1, 2, 3};
  int arr2[] = {1, 2, 3};
  memeq(c, arr1, arr2);
}

RUN_ALL(ADDTEST(c, memory_assertions););
