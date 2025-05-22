
#include "chest.h"

CHEST_TEST(numeric_assertions) {
  CHEST_COMPARE(c, EQ, 2 + 2, 4);
  CHEST_COMPARE(c, LT, -5, 0);
  CHEST_COMPARE(c, GT, 10, 5);
}

RUN_ALL(CHEST_ADD(c, numeric_assertions););
