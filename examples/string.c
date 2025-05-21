#include "chest.h"

TEST(string_assertions) {
  streq(c, "hello", "hello");
  streq(c, "foo", "bar");
}

RUN_ALL(ADDTEST(c, string_assertions););
