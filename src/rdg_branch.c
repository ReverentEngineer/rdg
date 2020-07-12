#include "rdg_branch.h"

#include "rdg_group.h"
#include "rdg_buffer.h"
#include "rdg_range.h"

#include <stdlib.h>
#include <string.h>

#define unlikely(x)    __builtin_expect(!!(x), 0)

enum node_type {
  NODE_ATOM,
  NODE_RANGE,
  NODE_GROUP
};

struct node {
  enum node_type type;
  union {
    struct {
      unsigned char* bytes;
      int size;
    } atom;
    struct rdg_range* range;
    struct rdg_group* group;
  } value;
  struct node* next; 
};

struct rdg_branch_iterator {
  enum node_type type;
  union {
    struct {
      unsigned char* bytes;
      int size;
    } atom;
    struct {
      struct rdg_range_iterator* iterator;
      struct rdg_range* self;
    } range;
    struct {
      struct rdg_group_iterator* group_iterator;
      struct rdg_branch_iterator* branch_iterator;
      struct rdg_group* self;
    } group;
  };
  struct rdg_branch_iterator *next;
};

struct rdg_branch {
  struct node *first;
  struct node *last;
  struct rdg_branch_iterator* iterator;
};

struct rdg_branch* rdg_branch_new() {
  return calloc(1, sizeof(struct rdg_branch));
}

static void iterator_free(struct rdg_branch_iterator* node) {
  if (node) {
    struct rdg_branch_iterator* next = node->next;
    free(node);
    iterator_free(next);
  }
}

void rdg_branch_free(struct rdg_branch* branch) {
  if (branch) {
    struct node *next = NULL, *tmp = NULL;
    next = branch->first;
    while (next != NULL) {
      tmp = next;
      next = tmp->next;
      switch(tmp->type) {
        case NODE_ATOM:
          free(tmp->value.atom.bytes);
          break;
        case NODE_RANGE:
          rdg_range_free(tmp->value.range);
          break;
        case NODE_GROUP:
          rdg_group_free(tmp->value.group);
          break;
      }
      free(tmp);
    }
    iterator_free(branch->iterator);
    free(branch);
  }
}

void rdg_branch_add_atom(struct rdg_branch* branch, char atom) {
  if ((branch->last == NULL && branch->first == NULL) || branch->last->type != NODE_ATOM) {
    struct node* node = malloc(sizeof(struct node));
    node->type = NODE_ATOM;
    node->value.atom.bytes = malloc(sizeof(char));
    memcpy(node->value.atom.bytes, &atom, 1);
    node->value.atom.size = 1;
    node->next = NULL;
    if (branch->last != NULL) {
      branch->last->next = node;

    } else {
      /* This means we have an empty branch */
      branch->first = node;
    }
    branch->last = node;
  } else if (branch->last->type == NODE_ATOM) {
      branch->last->value.atom.size++;
      branch->last->value.atom.bytes = realloc(branch->last->value.atom.bytes, branch->last->value.atom.size * sizeof(char));
      branch->last->value.atom.bytes[branch->last->value.atom.size - 1] = atom;
  }
}

void rdg_branch_add_range(struct rdg_branch* branch, struct rdg_range* range) {
  struct node* node = malloc(sizeof(struct node));
  node->next = NULL;
  node->type = NODE_RANGE;
  node->value.range = range;
  if (unlikely(branch->last == NULL)) {
    branch->first = node;
  } else {
    branch->last->next = node;
  }
  branch->last = node;
}

void rdg_branch_add_group(struct rdg_branch* branch, struct rdg_group* group) {
  struct node* node = malloc(sizeof(struct node));
  node->next = NULL;
  node->type = NODE_GROUP;
  node->value.group = group;
  if (unlikely(branch->last == NULL)) {
    branch->first = node;
  } else {
    branch->last->next = node;
  }
  branch->last = node;
}

static void iterator_build(struct rdg_branch_iterator** branch_iterator, struct node* branch_node) {
  if (branch_node != NULL) {
    *branch_iterator = malloc(sizeof(struct rdg_branch_iterator));
    (*branch_iterator)->type = branch_node->type;
    switch ((*branch_iterator)->type) {
      case NODE_ATOM:
        (*branch_iterator)->atom.bytes = branch_node->value.atom.bytes;
        (*branch_iterator)->atom.size = branch_node->value.atom.size;
        break;
      case NODE_RANGE:
        (*branch_iterator)->range.self = branch_node->value.range;
        (*branch_iterator)->range.iterator = rdg_range_begin(branch_node->value.range);
        break;
      case NODE_GROUP:
        (*branch_iterator)->group.self = branch_node->value.group;
        (*branch_iterator)->group.group_iterator = rdg_group_begin(branch_node->value.group);
        (*branch_iterator)->group.branch_iterator = rdg_branch_begin(rdg_group_get((*branch_iterator)->group.group_iterator));
        break;
    } 
    iterator_build(&(*branch_iterator)->next, branch_node->next);
  } else {
    (*branch_iterator) = NULL;
  }
}

struct rdg_branch_iterator* rdg_branch_begin(struct rdg_branch* branch) {
  if (branch->iterator != NULL) {
    iterator_free(branch->iterator);
    branch->iterator = NULL;
  }
  
  iterator_build(&(branch->iterator), branch->first);
  return branch->iterator;
}


static void get(struct rdg_buffer* buffer, struct rdg_branch_iterator* node) {
  unsigned char value = 0;
  struct rdg_branch* branch = NULL;
  struct rdg_buffer* branch_permutation = NULL;
  unsigned char* data = NULL;
  size_t size = 0;
  if (node != NULL) {
    switch (node->type) {
      case NODE_ATOM:
        rdg_buffer_append(buffer, node->atom.bytes, node->atom.size);
        break;
      case NODE_RANGE:
        value = rdg_range_get(node->range.iterator);
        rdg_buffer_append(buffer, &value, 1);
        break;
      case NODE_GROUP:
        branch_permutation = rdg_branch_get(node->group.branch_iterator);
        size = rdg_buffer_size(branch_permutation);
        data = rdg_buffer_release(branch_permutation);
        rdg_buffer_append(buffer, data, size);
        free(data);
        break;
    }
    get(buffer, node->next);
  }
 
}

struct rdg_buffer* rdg_branch_get(struct rdg_branch_iterator* iterator) {
  struct rdg_buffer* buffer = rdg_buffer_new();
  get(buffer, iterator);
  return buffer;
}

static void reset_iterators(struct rdg_branch_iterator* node) {
  if (node) {
    switch (node->type) {
      case NODE_ATOM:
        break;
      case NODE_RANGE:
        node->range.iterator = rdg_range_begin(node->range.self);
        break;
      case NODE_GROUP:
        node->group.group_iterator = rdg_group_begin(node->group.self);
        break;
    }
  }
}

static int next(struct rdg_branch_iterator* node) {
  int result = 0;
  struct rdg_branch* branch = NULL;
  if (node != NULL) {
    switch (node->type) {
      case NODE_ATOM:
        result = next(node->next);
        break;
      case NODE_RANGE:
        if (!next(node->next)) {
          if (rdg_range_next(node->range.iterator)) {
            reset_iterators(node->next);
            result = 1;
          }
        } else {
          result = 1;
        }
        break;
      case NODE_GROUP:
        if (!next(node->next)) {
          if (rdg_branch_next(node->group.branch_iterator)) {
            reset_iterators(node->next);
            result = 1;
          } else {
            if (rdg_group_next(node->group.group_iterator)) {
              node->group.branch_iterator = rdg_branch_begin(rdg_group_get(node->group.group_iterator));
              reset_iterators(node->next);
              result = 1;
            }
          }
        } else {
          result = 1;
        }
        break;
    }
  }
  return result;
}


int rdg_branch_next(struct rdg_branch_iterator* iterator) {
  return next(iterator);
}


int rdg_branch_permutations(struct rdg_branch* branch) {
  struct node* current = branch->first;
  int size = 0;
  while (current != NULL) {
    if (unlikely(size == 0)) {
      switch (current->type) {
        case NODE_ATOM:
          size = 1;
          break;
        case NODE_RANGE:
          size = rdg_range_permutations(current->value.range);
          break;
        case NODE_GROUP:
          size = rdg_group_permutations(current->value.group);
          break;
      } 
    } else {
      switch (current->type) {
        case NODE_ATOM:
          break;
        case NODE_RANGE:
          size *= rdg_range_permutations(current->value.range);
          break;
        case NODE_GROUP:
          size *= rdg_group_permutations(current->value.group);
          break;
      }
    }
    current = current->next;
  } 
  return size;
}

