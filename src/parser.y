%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { struct rdg* rdg }
%parse-param { set_trunk_cb set_trunk }

%{
  #include <stdio.h>
  #include "rdg.h"
  #include "rdg_atom.h"
  #include "rdg_branch.h"
  #include "rdg_group.h"
  #include "rdg_range.h"
  typedef void (*set_trunk_cb)(struct rdg*, struct rdg_branch*);
  #ifndef YY_TYPEDEF_YY_SCANNER_T
  #define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
  #endif
  int yylex();
  int yyerror(yyscan_t scanner, struct rdg* rdg, set_trunk_cb set_trunk, const char *msg);
%}
%pure-parser
%union {
  struct rdg_range* rangeval;
  char* strval;
  char charval;
  struct rdg_branch* branchval;
  struct rdg_group* groupval;
}

%token ANY
%token LITERAL
%token BYTE
%token TO
%token BEGIN_BRACKET
%token END_BRACKET
%token BEGIN_GROUP
%token END_GROUP
%token BRANCH

%type <rangeval> range
%type <rangeval> range_expression
%type <strval> BYTE
%type <charval>  atom
%type <charval> LITERAL
%type <groupval> group;
%type <groupval> branches;
%type <branchval> branch;

%%
trunk:
  branch { 
    set_trunk(rdg, $1);
}
;
atom:
  LITERAL { $$ = $1; }
  | BYTE { $$ = rdg_byte_to_atom($1); } 
;
range:
  BEGIN_BRACKET range_expression END_BRACKET { $$ = $2; } 
;
group:
     BEGIN_GROUP branches END_GROUP { $$ = $2 }
;
branches:
     branch { $$ = rdg_group_new(); (void) rdg_group_add_branch($$, $1); }
    | branches BRANCH branch { $$ = $1; (void) rdg_group_add_branch($1, $3); }
;
branch:
      atom { $$ = rdg_branch_new(); (void) rdg_branch_add_atom($$, $1); }
      | range { $$ = rdg_branch_new(); (void) rdg_branch_add_range($$, $1); }
      | group { $$ = rdg_branch_new(); (void) rdg_branch_add_group($$, $1); }
      | branch atom { $$ = $1; rdg_branch_add_atom($1, $2); }
      | branch range { $$ = $1; rdg_branch_add_range($1, $2); }
      | branch group { $$ = $1; rdg_branch_add_group($1, $2); }
;
range_expression:
  atom { $$ = rdg_range_new(); (void) rdg_range_append_atom($$, $1); }
  | atom TO atom { $$ = rdg_range_new_inclusive($1, $3); }
  | range_expression atom { $$ = $1; (void) rdg_range_append_atom($1, $2); }
  | range_expression atom TO atom { 
    struct rdg_range* b = rdg_range_new_inclusive($2, $4);
    (void) rdg_range_append($1, b);
    $$ = $1;
    rdg_range_free(b);
  }
%%
