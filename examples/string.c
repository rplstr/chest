#include "chest.h"

CHEST_TEST(string_assertions) {
  CHEST_STREQ(c, "hello", "hello");
  CHEST_STREQ(c, "foo", "bar");
}

RUN_ALL(CHEST_ADD(c, string_assertions););
