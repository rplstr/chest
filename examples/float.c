#include "chest.h"

CHEST_TEST(float_assertions) {
  // 0.1 + 0.2 may not equal 0.3 exactly, so we use a tolerance
  CHEST_FPEQ(c, 0.1 + 0.2, 0.3, 1e-6);
}

CHEST_RUN_ALL(CHEST_ADD(c, float_assertions););
