/* SPDX-License-Identifier: 0BSD */
/*
 * chest.h — a simple C99 testing framework.
 */

/*
 *
 * CHEST_DESC_LT          Text for 'less than' cmp (default: "LESS THAN")
 * CHEST_DESC_LE          Text for 'less/equal' cmp (default: "LESS THAN OR
 * EQUAL TO")
 * CHEST_DESC_GT          Text for 'greater than' cmp (default: "GREATER THAN")
 * CHEST_DESC_GE          Text for 'greater/equal' cmp (default: "GREATER THAN
 * OR EQUAL TO")
 * CHEST_DESC_EQ          Text for 'equal' cmp (default: "EQUAL")
 * CHEST_DESC_NE          Text for 'not equal' cmp (default: "NOT EQUAL")
 *
 * CHEST_PASS_STR         Text printed on test pass (default: "PASS")
 * CHEST_FAIL_STR         Text printed on test fail (default: "FAIL")
 *
 * CHEST_MEASURE          Enable per-test timing (includes <time.h>) if defined
 * CHEST_DEFAULT_TERM_WIDTH Terminal width for alignment (default: 80)
 *
 * CHEST_COLORED_OUTPUT   Enable colored output if defined
 * CHEST_PASS_COLOR       ANSI for pass (default: "\x1b[32m\x1b[1m")
 * CHEST_FAIL_COLOR       ANSI for fail (default: "\x1b[31m\x1b[1m")
 * CHEST_MEASURE_COLOR    ANSI for timing (default: "\x1b[90m")
 * CHEST_RESET_COLOR      ANSI reset (default: "\x1b[0m")
 *
 * CHEST_MALLOC           Allocator macro (default: malloc)
 * CHEST_REALLOC          Reallocator macro (default: realloc)
 * CHEST_FREE             Deallocator macro (default: free)
 */

#ifndef CHEST_H_
#define CHEST_H_

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef CHEST_DESC_LT
#define CHEST_DESC_LT "LESS THAN"
#endif
#ifndef CHEST_DESC_LE
#define CHEST_DESC_LE "LESS THAN OR EQUAL TO"
#endif
#ifndef CHEST_DESC_GT
#define CHEST_DESC_GT "GREATER THAN"
#endif
#ifndef CHEST_DESC_GE
#define CHEST_DESC_GE "GREATER THAN OR EQUAL TO"
#endif
#ifndef CHEST_DESC_EQ
#define CHEST_DESC_EQ "EQUAL"
#endif
#ifndef CHEST_DESC_NE
#define CHEST_DESC_NE "NOT EQUAL"
#endif
#define DESC_STR(op)                                                           \
  ((op) == CHEST_CMP_LT   ? CHEST_DESC_LT                                      \
   : (op) == CHEST_CMP_LE ? CHEST_DESC_LE                                      \
   : (op) == CHEST_CMP_GT ? CHEST_DESC_GT                                      \
   : (op) == CHEST_CMP_GE ? CHEST_DESC_GE                                      \
   : (op) == CHEST_CMP_EQ ? CHEST_DESC_EQ                                      \
   : (op) == CHEST_CMP_NE ? CHEST_DESC_NE                                      \
                          : "")

#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t

#ifndef CHEST_PASS_STR
#define CHEST_PASS_STR "PASS"
#endif
#ifndef CHEST_FAIL_STR
#define CHEST_FAIL_STR "FAIL"
#endif

/* timing measurement */
#ifdef CHEST_MEASURE
#include <time.h>
#endif

/* colored output */
#ifdef CHEST_COLORED_OUTPUT
#ifndef CHEST_PASS_COLOR
#define CHEST_PASS_COLOR "\x1b[32m\x1b[1m"
#endif
#ifndef CHEST_FAIL_COLOR
#define CHEST_FAIL_COLOR "\x1b[31m\x1b[1m"
#endif
#ifndef CHEST_MEASURE_COLOR
#define CHEST_MEASURE_COLOR "\x1b[90m"
#endif
#ifndef CHEST_RESET_COLOR
#define CHEST_RESET_COLOR "\x1b[0m"
#endif
#else
#ifndef CHEST_PASS_COLOR
#define CHEST_PASS_COLOR ""
#endif
#ifndef CHEST_FAIL_COLOR
#define CHEST_FAIL_COLOR ""
#endif
#ifndef CHEST_MEASURE_COLOR
#define CHEST_MEASURE_COLOR ""
#endif
#ifndef CHEST_RESET_COLOR
#define CHEST_RESET_COLOR ""
#endif
#endif

#ifndef CHEST_DEFAULT_TERM_WIDTH
#define CHEST_DEFAULT_TERM_WIDTH 80
#endif

#define LT CHEST_CMP_LT
#define LE CHEST_CMP_LE
#define GT CHEST_CMP_GT
#define GE CHEST_CMP_GE
#define EQ CHEST_CMP_EQ
#define NE CHEST_CMP_NE

#define OPSTR_LT "<"
#define OPSTR_LE "<="
#define OPSTR_GT ">"
#define OPSTR_GE ">="
#define OPSTR_EQ "=="
#define OPSTR_NE "!="

#define assertcmp(ctx, op, A, B)                                               \
  chest_assert_cmp((ctx), op, (long double)(A), (long double)(B),              \
                   #A " " OPSTR_##op " " #B, __FILE__, __LINE__)

#define memeq(ctx, X, Y)                                                       \
  chest_memeq((ctx), &(X), &(Y), sizeof(X), #X " == " #Y, __FILE__, __LINE__)

#define fpeq(ctx, A, B, tol)                                                   \
  chest_fpeq((ctx), (long double)(A), (long double)(B), (long double)(tol),    \
             #A " ≈ " #B, __FILE__, __LINE__)

#define streq(ctx, A, B)                                                       \
  chest_streq((ctx), (A), (B), #A " == " #B, __FILE__, __LINE__)

#define TEST(name) static void name(chest_t *c)

#define ADDTEST(c, name) chest_addtest(c, name, #name)

#define RUN_BEFORE(c, fn) chest_set_before_all((c), (fn))
#define RUN_AFTER(c, fn) chest_set_after_all((c), (fn))
#define RUN_BEFORE_EACH(c, fn) chest_set_before_each((c), (fn))
#define RUN_AFTER_EACH(c, fn) chest_set_after_each((c), (fn))

#define RUN_ALL(...)                                                           \
  int main(void) {                                                             \
    chest_t *c = chest_init();                                                 \
    if (c == NULL)                                                             \
      return 1;                                                                \
    __VA_ARGS__;                                                               \
    chest_error_t res = chest_run(c);                                          \
    chest_summary(c);                                                          \
    chest_destroy(c);                                                          \
    return (int)res;                                                           \
  }

#ifndef CHEST_PRINT
#define CHEST_PRINT(...) printf(__VA_ARGS__)
#endif

#ifndef CHEST_THREAD_SAFE
#define CHEST_THREAD_SAFE 0
#endif
#if CHEST_THREAD_SAFE
#include <threads.h>
#define CHEST_LOCK(ctx) mtx_lock(&((ctx)->lock))
#define CHEST_UNLOCK(ctx) mtx_unlock(&((ctx)->lock))
#else
#define CHEST_LOCK(ctx) ((void)0)
#define CHEST_UNLOCK(ctx) ((void)0)
#endif

/**
 * Error codes returned by chest API
 */
typedef enum chest_error_e {
  CHEST_OK = 0,
  CHEST_ERR_ASSERT,
  CHEST_ERR_INTERNAL
} chest_error_t;

/**
 * Comparison operators for assertcmp
 */
typedef enum chest_cmp_op_e {
  CHEST_CMP_LT,
  CHEST_CMP_LE,
  CHEST_CMP_GT,
  CHEST_CMP_GE,
  CHEST_CMP_EQ,
  CHEST_CMP_NE
} chest_cmp_op_t;

typedef struct chest_ctx_s chest_t;
typedef void (*testfn_t)(chest_t *c);

struct chest_ctx_s {
  testfn_t *tests;
  char **names;
  size_t *name_lens;
  size_t count;
  size_t cap;
  size_t failures;
  size_t max_name_len;
  char *last_msg;
  bool *results;
  char **messages;
#if CHEST_THREAD_SAFE
  mtx_t lock; /* context mutex */
#endif
  /* suite/test setup/teardown hooks */
  testfn_t before_all;  /* run once before all tests */
  testfn_t after_all;   /* run once after all tests */
  testfn_t before_each; /* run before each test */
  testfn_t after_each;  /* run after each test */
};

#ifndef CHEST_MALLOC
#define CHEST_MALLOC(size) malloc(size)
#endif
#ifndef CHEST_REALLOC
#define CHEST_REALLOC(ptr, size) realloc(ptr, size)
#endif
#ifndef CHEST_FREE
#define CHEST_FREE(ptr) free(ptr)
#endif

/**
 * chest_init — allocate and initialize test context
 * @return: new context pointer or NULL on allocation failure
 */
static inline chest_t *chest_init(void) {
  chest_t *c = (chest_t *)CHEST_MALLOC(sizeof *c);
  if (c == NULL)
    return NULL;
  c->tests = NULL;
  c->names = NULL;
  c->name_lens = NULL;
  c->count = 0;
  c->cap = 0;
  c->failures = 0;
  c->max_name_len = 0;
  c->last_msg = NULL;
  c->results = NULL;  // init results array
  c->messages = NULL; // init messages array
#if CHEST_THREAD_SAFE
  if (mtx_init(&c->lock, mtx_plain) != thrd_success) {
    CHEST_FREE(c);
    return NULL;
  }
#endif
  /* init hooks */
  c->before_all = NULL;
  c->after_all = NULL;
  c->before_each = NULL;
  c->after_each = NULL;
  return c;
}

/**
 * chest_destroy — free test context and associated resources
 * @c: context to destroy (NULL safe)
 */
static inline void chest_destroy(chest_t *c) {
  if (c != NULL) {

    if (c->names) {
      for (size_t i = 0; i < c->count; ++i) {
        CHEST_FREE(c->names[i]);
      }
    }
    CHEST_FREE(c->tests);
    CHEST_FREE(c->names);
    CHEST_FREE(c->name_lens);
    if (c->results)
      CHEST_FREE(c->results);
    if (c->messages) { // free messages
      for (size_t i = 0; i < c->count; ++i)
        if (c->messages[i])
          CHEST_FREE(c->messages[i]);
      CHEST_FREE(c->messages);
    }
#if CHEST_THREAD_SAFE
    mtx_destroy(&c->lock);
#endif
    if (c->last_msg)
      CHEST_FREE(c->last_msg);
    CHEST_FREE(c);
  }
}

/**
 * chest_report — format and print test result and optional timing
 * @c: test context
 * @name:      display name (no 'test_' prefix; '_' as spaces)
 * @name_len:  length of display name
 * @passed:    non-zero on success, zero on failure
 * @test_ms:   test execution time in ms (if CHEST_MEASURE)
 * @over_ms:   framework overhead in ms (if CHEST_MEASURE)
 * @term_width:terminal columns for flush-right timing
 */
static inline void chest_report(chest_t *c, const char *name, size_t name_len,
                                int passed, double test_ms, double over_ms,
                                size_t term_width) {
  /* print aligned name and PASS/FAIL */
  CHEST_PRINT("%-*.*s ... %s%s%s", (int)c->max_name_len, (int)name_len, name,
              (passed ? CHEST_PASS_COLOR : CHEST_FAIL_COLOR),
              (passed ? CHEST_PASS_STR : CHEST_FAIL_STR), CHEST_RESET_COLOR);
  /* print timing if enabled */
#ifdef CHEST_MEASURE
  CHEST_PRINT("\t\t%s%.3fms%s + %s%.3fms%s", CHEST_MEASURE_COLOR, test_ms,
              CHEST_RESET_COLOR, CHEST_MEASURE_COLOR, over_ms,
              CHEST_RESET_COLOR);
#endif
  putc('\n', stdout);
  /* print assertion message after report */
  if (!passed && c->last_msg) {
    CHEST_PRINT("%s", c->last_msg);
    CHEST_FREE(c->last_msg);
    c->last_msg = NULL;
  }
}

/**
 * chest_addtest — register a test function
 * @c:    test context (non-NULL)
 * @fn:   test function pointer
 * @name: test name string
 * @return: CHEST_OK on success or CHEST_ERR_INTERNAL on error
 */
static inline chest_error_t chest_addtest(chest_t *c, testfn_t fn,
                                          const char *name) {
  if (!c || !fn || !name)
    return CHEST_ERR_INTERNAL;
  /* grow arrays safely */
  if (c->count == c->cap) {
    size_t oldcap = c->cap;
    if (oldcap > SIZE_MAX / 2)
      return CHEST_ERR_INTERNAL;
    size_t newcap = oldcap ? oldcap * 2 : 4;
    /* Allocate new buffers */
    testfn_t *nt = CHEST_MALLOC(newcap * sizeof *nt);
    char **nn = CHEST_MALLOC(newcap * sizeof *nn);
    size_t *nl = CHEST_MALLOC(newcap * sizeof *nl);
    bool *nr = CHEST_MALLOC(newcap * sizeof *nr);
    char **nm = CHEST_MALLOC(newcap * sizeof *nm);
    if (!nt || !nn || !nl || !nr || !nm) {
      CHEST_FREE(nt);
      CHEST_FREE(nn);
      CHEST_FREE(nl);
      CHEST_FREE(nr);
      CHEST_FREE(nm);
      return CHEST_ERR_INTERNAL;
    }
    /* Copy existing entries */
    if (oldcap) {
      memcpy(nt, c->tests, oldcap * sizeof *nt);
      memcpy(nn, c->names, oldcap * sizeof *nn);
      memcpy(nl, c->name_lens, oldcap * sizeof *nl);
      memcpy(nr, c->results, oldcap * sizeof *nr);
      memcpy(nm, c->messages, oldcap * sizeof *nm);
    }
    /* init new slots */
    for (size_t j = oldcap; j < newcap; ++j) {
      nr[j] = false;
      nm[j] = NULL;
    }
    /* Free old arrays */
    CHEST_FREE(c->tests);
    CHEST_FREE(c->names);
    CHEST_FREE(c->name_lens);
    CHEST_FREE(c->results);
    CHEST_FREE(c->messages);
    /* Update context */
    c->tests = nt;
    c->names = nn;
    c->name_lens = nl;
    c->results = nr;
    c->messages = nm;
    c->cap = newcap;
  }
  /* Prepare display name */
  const char *src = name;
  if (strncmp(src, "test_", 5) == 0) {
    src += 5;
  }
  size_t len = strlen(src);
  char *proc = CHEST_MALLOC(len + 1);
  if (!proc) {
    return CHEST_ERR_INTERNAL;
  }
  for (size_t i = 0; i < len; ++i) {
    proc[i] = (src[i] == '_' ? ' ' : src[i]);
  }
  proc[len] = '\0';
  /* Register test */
  c->tests[c->count] = fn;
  c->names[c->count] = proc;
  c->name_lens[c->count] = len;
  if (len > c->max_name_len) {
    c->max_name_len = len;
  }
  c->count++;
  return CHEST_OK;
}

/**
 * chest_run — execute all registered tests
 * @c: test context (non-NULL)
 * @return: CHEST_OK if all passed, CHEST_ERR_ASSERT if any failure
 */
static inline chest_error_t chest_run(chest_t *c) {
#if CHEST_THREAD_SAFE
  CHEST_LOCK(c);
#endif
  if (!c)
    return CHEST_ERR_INTERNAL;
  /* context sanity */
  if (c->count > c->cap || !c->tests || !c->names || !c->results ||
      !c->messages) {
    return CHEST_ERR_INTERNAL;
  }
  const size_t term_width = CHEST_DEFAULT_TERM_WIDTH;
  if (c->before_all)
    c->before_all(c);
  for (size_t idx = 0; idx < c->count; ++idx) {
    if (c->before_each)
      c->before_each(c);
    /* track failures before running */
    size_t baseline = c->failures;
#ifdef CHEST_MEASURE
    clock_t start = clock();
#endif
    c->tests[idx](c);
#ifdef CHEST_MEASURE
    clock_t mid = clock();
#endif
    bool passed = (c->failures == baseline);
    c->results[idx] = passed; /* record outcome */
    /* store detailed failure message */
    if (!passed && c->last_msg) {
      size_t msglen = strlen(c->last_msg) + 1;
      char *saved = (char *)CHEST_MALLOC(msglen);
      if (saved)
        memcpy(saved, c->last_msg, msglen);
      c->messages[idx] = saved;
    }
#ifdef CHEST_MEASURE
    double test_ms = (double)(mid - start) * 1000.0 / CLOCKS_PER_SEC;
    clock_t end = clock();
    double over_ms = (double)(end - mid) * 1000.0 / CLOCKS_PER_SEC;
    chest_report(c, c->names[idx], c->name_lens[idx], passed, test_ms, over_ms,
                 term_width);
#else
    chest_report(c, c->names[idx], c->name_lens[idx], passed, 0, 0, term_width);
#endif
    if (c->after_each)
      c->after_each(c);
  }
  if (c->after_all)
    c->after_all(c);
#if CHEST_THREAD_SAFE
  CHEST_UNLOCK(c);
#endif
  return c->failures ? CHEST_ERR_ASSERT : CHEST_OK;
}

/**
 * chest_set_before_all — set before_all hook
 * @c: test context (non-NULL)
 * @fn: hook function pointer
 * @return: CHEST_OK on success or CHEST_ERR_INTERNAL on error
 */
static inline chest_error_t chest_set_before_all(chest_t *c, testfn_t fn) {
  if (!c)
    return CHEST_ERR_INTERNAL;
  c->before_all = fn;
  return CHEST_OK;
}

/**
 * chest_set_after_all — set after_all hook
 * @c: test context (non-NULL)
 * @fn: hook function pointer
 * @return: CHEST_OK on success or CHEST_ERR_INTERNAL on error
 */
static inline chest_error_t chest_set_after_all(chest_t *c, testfn_t fn) {
  if (!c)
    return CHEST_ERR_INTERNAL;
  c->after_all = fn;
  return CHEST_OK;
}

/**
 * chest_set_before_each — set before_each hook
 * @c: test context (non-NULL)
 * @fn: hook function pointer
 * @return: CHEST_OK on success or CHEST_ERR_INTERNAL on error
 */
static inline chest_error_t chest_set_before_each(chest_t *c, testfn_t fn) {
  if (!c)
    return CHEST_ERR_INTERNAL;
  c->before_each = fn;
  return CHEST_OK;
}

/**
 * chest_set_after_each — set after_each hook
 * @c: test context (non-NULL)
 * @fn: hook function pointer
 * @return: CHEST_OK on success or CHEST_ERR_INTERNAL on error
 */
static inline chest_error_t chest_set_after_each(chest_t *c, testfn_t fn) {
  if (!c)
    return CHEST_ERR_INTERNAL;
  c->after_each = fn;
  return CHEST_OK;
}

/**
 * memeq_impl — binary compare any POD object
 * @c:     non-NULL test context
 * @A, B:  pointers to objects
 * @N:     size in bytes
 * @expr:  textual expression for logging
 * @file:  source file name
 * @line:  source line number
 */
static inline chest_error_t chest_memeq(chest_t *c, const void *A,
                                        const void *B, size_t N,
                                        const char *expr, const char *file,
                                        int line) {
  chest_error_t result = CHEST_ERR_INTERNAL;
  bool mismatch = false;
  size_t i = 0U;
  size_t w = sizeof(uintptr_t);

  if (c != NULL) {
    const uint8_t *a = (const uint8_t *)A;
    const uint8_t *b = (const uint8_t *)B;

    for (; (i + w) <= N; i += w) {
      uintptr_t va = 0U;
      uintptr_t vb = 0U;
      (void)memcpy(&va, &a[i], w);
      (void)memcpy(&vb, &b[i], w);
      if (va != vb) {
        mismatch = true;
        break;
      }
    }

    for (; (!mismatch) && (i < N); ++i) {
      if (a[i] != b[i]) {
        mismatch = true;
      }
    }

    result = mismatch ? CHEST_ERR_ASSERT : CHEST_OK;
    if (result == CHEST_ERR_ASSERT) {
      c->failures++;
      if (c->last_msg)
        CHEST_FREE(c->last_msg);
      size_t _len =
          snprintf(NULL, 0, "  %s is false. (%s:%d)\n", expr, file, line) + 1;
      c->last_msg = (char *)CHEST_MALLOC(_len);
      snprintf(c->last_msg, _len, "  %s is false. (%s:%d)\n", expr, file, line);
    }
  }

  return result;
}

/**
 * fpeq_impl — float approximate equality
 * @c:     non-NULL test context
 * @A, B:  floating-point values
 * @tol:   tolerance
 * @expr:  textual expression for logging
 * @file:  source file name
 * @line:  source line number
 */
static inline chest_error_t chest_fpeq(chest_t *c, long double A, long double B,
                                       long double tol, const char *expr,
                                       const char *file, int line) {
  chest_error_t result = CHEST_ERR_INTERNAL;

  if (c != NULL) {
    long double delta = fabsl(A - B);
    result = (delta <= tol) ? CHEST_OK : CHEST_ERR_ASSERT;
    if (result == CHEST_ERR_ASSERT) {
      c->failures++;
      if (c->last_msg)
        CHEST_FREE(c->last_msg);
      size_t _len =
          snprintf(
              NULL, 0,
              "  %Lg is not within threshold of %Lg (expected %Lg). (%s:%d)\n",
              A, tol, B, file, line) +
          1;
      c->last_msg = (char *)CHEST_MALLOC(_len);
      snprintf(c->last_msg, _len,
               "  %Lg is not within threshold of %Lg (expected %Lg). (%s:%d)\n",
               A, tol, B, file, line);
    }
  }

  return result;
}

/**
 * streq_impl — C-string null-terminated equality
 * @c:     non-NULL test context
 * @A, B:  C-strings
 * @expr:  textual expression for logging
 * @file:  source file name
 * @line:  source line number
 */
static inline chest_error_t chest_streq(chest_t *c, const char *A,
                                        const char *B, const char *expr,
                                        const char *file, int line) {
  chest_error_t result = CHEST_ERR_INTERNAL;

  if ((c != NULL) && (A != NULL) && (B != NULL)) {
    result = (strcmp(A, B) == 0) ? CHEST_OK : CHEST_ERR_ASSERT;
    if (result == CHEST_ERR_ASSERT) {
      c->failures++;
      if (c->last_msg)
        CHEST_FREE(c->last_msg);
      size_t _len =
          snprintf(NULL, 0, "  '%s' and '%s' are not EQUAL. (%s:%d)\n", A, B,
                   file, line) +
          1;
      c->last_msg = (char *)CHEST_MALLOC(_len);
      snprintf(c->last_msg, _len, "  '%s' and '%s' are not EQUAL. (%s:%d)\n", A,
               B, file, line);
    }
  }

  return result;
}

/**
 * chest_assert_cmp — generic numeric comparison assertion
 */
static inline chest_error_t chest_assert_cmp(chest_t *c, chest_cmp_op_t op,
                                             long double A, long double B,
                                             const char *expr, const char *file,
                                             int line) {
  chest_error_t res = CHEST_ERR_INTERNAL;
  bool ok = false;
  if (c != NULL) {
    switch (op) {
    case CHEST_CMP_LT:
      ok = (A < B);
      break;
    case CHEST_CMP_LE:
      ok = (A <= B);
      break;
    case CHEST_CMP_GT:
      ok = (A > B);
      break;
    case CHEST_CMP_GE:
      ok = (A >= B);
      break;
    case CHEST_CMP_EQ:
      ok = (A == B);
      break;
    case CHEST_CMP_NE:
      ok = (A != B);
      break;
    default:
      ok = false;
      break;
    }
    res = ok ? CHEST_OK : CHEST_ERR_ASSERT;
    if (res == CHEST_ERR_ASSERT) {
      c->failures++;
      if (c->last_msg)
        CHEST_FREE(c->last_msg);
      const char *desc = DESC_STR(op);
      size_t _len = snprintf(NULL, 0, "  '%Lg' is not %s '%Lg'. (%s:%d)\n", A,
                             desc, B, file, line) +
                    1;
      c->last_msg = (char *)CHEST_MALLOC(_len);
      snprintf(c->last_msg, _len, "  '%Lg' is not %s '%Lg'. (%s:%d)\n", A, desc,
               B, file, line);
    }
  }
  return res;
}

/**
 * chest_summary — print overall test summary and failed names
 */
static inline void chest_summary(chest_t *c) {
  if (!c)
    return;
  size_t passed = c->count - c->failures;
  CHEST_PRINT("---\n");
  CHEST_PRINT("%zu/%zu PASSED\n", passed, c->count);
  CHEST_PRINT("%zu FAILED\n", c->failures);
  if (c->failures) {
    for (size_t i = 0; i < c->count; ++i) {
      if (!c->results[i]) {
        CHEST_PRINT("%s\n", c->names[i]);
        if (c->messages[i])
          CHEST_PRINT("%s", c->messages[i]);
      }
    }
  }
}

#endif /* CHEST_H_ */
