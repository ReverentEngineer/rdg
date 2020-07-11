#include "rdg_group.h"
#include "rdg_branch.h"

#include <stdlib.h>

struct rdg_group_iterator {
  struct rdg_group_member* current;
};

struct rdg_group_member {
  struct rdg_branch       *branch;
  struct rdg_group_member *next;
};

struct rdg_group {
  struct rdg_group_member *first;
  struct rdg_group_iterator iterator;
};

struct rdg_group* rdg_group_new() {
  return calloc(1, sizeof(struct rdg_group));
}

void rdg_group_free(struct rdg_group* group) {
  if (group) {
    struct rdg_group_member *next = NULL, *tmp = NULL;
    next = group->first;
    while (next != NULL) {
      tmp = next;
      next = tmp->next;
      rdg_branch_free(tmp->branch);
      free(tmp);
    }
    free(group);
  }
}

void rdg_group_add_branch(struct rdg_group* group, struct rdg_branch* branch) {
  struct rdg_group_member* member = malloc(sizeof(struct rdg_group_member));
  struct rdg_group_member *current = NULL;
  member->branch = branch;
  member->next = NULL;
  if (group->first == NULL) {
    group->first = member;
  } else {
    current = group->first;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = member;
  }
}

struct rdg_group_iterator* rdg_group_begin(struct rdg_group* group) {
  group->iterator.current = group->first;
  return &(group->iterator);
}

int rdg_group_next(struct rdg_group_iterator* iterator) {
  if (iterator->current) {
      iterator->current = iterator->current->next;
      return (iterator->current != NULL) ? 1 : 0;
  } else {
    return 0;
  }
}

struct rdg_branch* rdg_group_get(const struct rdg_group_iterator* iterator) {
  if (iterator->current) {
    return iterator->current->branch;
  } else {
    return NULL;
  }
}

int rdg_group_permutations(const struct rdg_group* group) {
  struct rdg_group_member* member = NULL;
  int size = 0;
  if (group->first != NULL) {
    size = rdg_branch_permutations(group->first->branch);
    member = group->first->next;
    while (member != NULL) {
      size += rdg_branch_permutations(member->branch);
      member = member->next;
    }
  }
  return size;
}
