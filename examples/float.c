#include "chest.h"

TEST(float_assertions) {
  // 0.1 + 0.2 may not equal 0.3 exactly, so we use a tolerance
  fpeq(c, 0.1 + 0.2, 0.3, 1e-6);
}

RUN_ALL(ADDTEST(c, float_assertions););
