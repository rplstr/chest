
#include "chest.h"

TEST(numeric_assertions) {
  assertcmp(c, EQ, 2 + 2, 4);
  assertcmp(c, LT, -5, 0);
  assertcmp(c, GT, 10, 5);
}

RUN_ALL(ADDTEST(c, numeric_assertions););
