#include "rdg.h"

#include "rdg_branch.h"
#include "rdg_buffer.h"
#include "rdg_range.h"

#include "parser.tab.h"
#include "lexer.yy.h"

#define unlikely(x)    __builtin_expect(!!(x), 0)

struct rdg {
  struct rdg_branch* trunk;
  struct rdg_branch_iterator* iterator;
};

int yyparse(yyscan_t scanner, struct rdg* rdg, void (*set_trunk)(struct rdg*, struct rdg_branch*));

int yyerror(yyscan_t scanner, struct rdg* rdg, void (*set_trunk)(struct rdg*, struct rdg_branch*), const char *msg) {
    return 0;
}

static void set_trunk(struct rdg* rdg, struct rdg_branch* branch) {
  rdg->trunk = branch;
}

struct rdg* rdg_new(const char* expression) {
  struct rdg* rdg = calloc(1, sizeof(rdg));
  yyscan_t scanner;
  if (yylex_init(&scanner)) {
    return NULL;
  }
  YY_BUFFER_STATE buffer = yy_scan_string(expression, scanner);
  yyparse(scanner, rdg, set_trunk);
  yy_delete_buffer(buffer, scanner);
  yylex_destroy(scanner);
  rdg->iterator = rdg_branch_begin(rdg->trunk);
  return rdg;
}

int rdg_generate(unsigned char **result, size_t *size, struct rdg* rdg) {
  int rc = 0;
  struct rdg_buffer* buffer = NULL;
  if (rdg->iterator) {
    buffer = rdg_branch_get(rdg->iterator); 
    if (buffer) {
      if (size != NULL) {
        *size = rdg_buffer_size(buffer);
      }
      if (*result != NULL) {
        *result = rdg_buffer_release(buffer);
      }
    }
    if (!rdg_branch_next(rdg->iterator)) {
      rdg->iterator = NULL;
      rc = 1;
    }
  }
  return rc; 
}

int rdg_permutations(const struct rdg* rdg) {
  return rdg_branch_permutations(rdg->trunk);
}

void rdg_free(struct rdg* rdg) {
  if (rdg) {
    if (rdg->trunk) {
      rdg_branch_free(rdg->trunk);
    }
  }
}
