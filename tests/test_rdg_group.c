#include "rdg_group.h"
#include "rdg_branch.h"

#ifndef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>

int main() {
  struct rdg_group *group = NULL;
  struct rdg_group_iterator *iter = NULL;
  struct rdg_branch *branch1 = NULL, *branch2 = NULL;

  group = rdg_group_new();
  assert(group != NULL);

  assert(rdg_group_permutations(group) == 0);

  branch1 = rdg_branch_new();
  (void) rdg_branch_add_atom(branch1, 'a');
  (void) rdg_group_add_branch(group, branch1);
  
  branch2 = rdg_branch_new();
  (void) rdg_branch_add_atom(branch2, 'b');
  (void) rdg_group_add_branch(group, branch2);

  assert(rdg_group_permutations(group) == 2);

  iter = rdg_group_begin(group);
  assert(iter != NULL);

  assert(rdg_group_get(iter) == branch1);
  assert(rdg_group_next(iter)); 
  assert(rdg_group_get(iter) == branch2); 
  assert(!rdg_group_next(iter)); 
  (void) rdg_group_free(group);
  return 0;
}
