#include "rdg.h"

#include "rdg_branch.h"
#include "rdg_buffer.h"
#include "rdg_range.h"

#include "parser.tab.h"
#include "lexer.yy.h"

struct rdg {
  struct rdg_branch* trunk;
  struct rdg_branch_iterator* iterator;
  struct rdg_buffer* buffer;
};

int yyparse(yyscan_t scanner, struct rdg* rdg, void (*set_trunk)(struct rdg*, struct rdg_branch*));

int yyerror(yyscan_t scanner, struct rdg* rdg, void (*set_trunk)(struct rdg*, struct rdg_branch*), const char *msg) {
    return 0;
}

static void set_trunk(struct rdg* rdg, struct rdg_branch* branch) {
  rdg->trunk = branch;
}

struct rdg* rdg_new(const char* expression) {
  struct rdg* rdg = NULL;
  if (strlen(expression) == 0) {
    return NULL;
  }

  rdg = malloc(sizeof(struct rdg));
  yyscan_t scanner;
  if (yylex_init(&scanner)) {
    free(rdg);
    return NULL;
  }
  YY_BUFFER_STATE buffer = yy_scan_string(expression, scanner);
  yyparse(scanner, rdg, set_trunk);
  yy_delete_buffer(buffer, scanner);
  yylex_destroy(scanner);
  if (rdg->trunk != NULL) {
    rdg->iterator = rdg_branch_begin(rdg->trunk);
    rdg->buffer = rdg_buffer_new(rdg_branch_max_size(rdg->trunk));
  } else {
    rdg_free(rdg);
    rdg = NULL;
  }
  return rdg;
}

int rdg_generate(const unsigned char **result, size_t *size, struct rdg* rdg) {
  int rc = 0;
  if (rdg->iterator) {
    rdg_buffer_reset(rdg->buffer);
    rdg_branch_get(rdg->buffer, rdg->iterator);
    if (size != NULL) {
      *size = rdg_buffer_size(rdg->buffer);
    }
    if (result != NULL) {
      *result = rdg_buffer_get(rdg->buffer);
    }
    rc = 1;
    if (!rdg_branch_next(rdg->iterator)) {
      rdg->iterator = NULL;
    }
  } else {
    if (size != NULL) {
      *size = 0;
    }
    if (result != NULL) {
      *result = NULL;
    }
  }
  return rc; 
}

size_t rdg_permutations(const struct rdg* rdg) {
  return rdg_branch_permutations(rdg->trunk);
}

void rdg_free(struct rdg* rdg) {
  if (rdg) {
    if (rdg->trunk) {
      rdg_branch_free(rdg->trunk);
    }
    if (rdg->buffer) {
      rdg_buffer_free(rdg->buffer);
    }
    free(rdg);
  }
}
