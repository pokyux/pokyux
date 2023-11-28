#ifdef PKX_TEST

#define check(expr) if (expr) \
    printf("[ok] %s\n", #expr); \
  else { \
    printf("[failed] %s\n", #expr); \
    exit(1); \
  }

#define checkeq(expra, exprb) check(expra == exprb)
#define checkneq(expra, exprb) check(expra != exprb)

typedef struct {
  char *test_name;
  void (*test_func)();
} test_unit;

#endif
