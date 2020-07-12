#include "rdg_range.h"

#include <stdlib.h>
#include <string.h>

enum color_t { RED, BLACK };

struct rdg_range_node {
  struct rdg_range_node *parent;
  struct rdg_range_node *left;
  struct rdg_range_node *right;
  enum color_t color;
  unsigned char value;
};

static int
compare(unsigned char lhs, unsigned char rhs) {
  return rhs - lhs;
}

struct rdg_range_iterator {
  struct rdg_range_node* node;
};

struct rdg_range {
  int   size;
  struct rdg_range_node* root;
  struct rdg_range_iterator iterator;
};

static void free_node(struct rdg_range_node* node) {
  if (node->right != NULL) {
    free_node(node->right);
  } else if (node->left != NULL) {
    free_node(node->left);
  }
  free(node);
}

struct rdg_range* rdg_range_new(void) {
  return calloc(1, sizeof(struct rdg_range));
}

struct rdg_range* rdg_range_new_inclusive(unsigned char from, unsigned char to) {
  struct rdg_range* range = malloc(sizeof(struct rdg_range));
  if (to <= from) {
    abort();
  }
  for (int i = 0; i <= to - from; i++) {
    rdg_range_append_atom(range, from + i);
  }
  return range; 
}

int rdg_range_permutations(const struct rdg_range* range) {
  return range->size;
}

void rdg_range_append(struct rdg_range* to, struct rdg_range* from) {
  struct rdg_range_iterator* it = rdg_range_begin(from);
  unsigned char value = 0;
  do {
    value = rdg_range_get(it);
    rdg_range_append_atom(to, value);
  } while(rdg_range_next(it) == 1);
}

static struct rdg_range_node *
get_sibling(struct rdg_range_node *node) {
  if (node->parent == NULL) {
    return NULL;
  }

  if (node == node->parent->left) {
    return node->parent->right;
  } else {
    return node->parent->left;
  }
}

static struct rdg_range_node *
get_parent(struct rdg_range_node *node) {
  return node == NULL ? NULL : node->parent;
}

static struct rdg_range_node *
get_grand_parent(struct rdg_range_node *node) {
  return get_parent(get_parent(node));
}

static struct rdg_range_node *
get_uncle(struct rdg_range_node *node) {
  struct rdg_range_node *parent = get_parent(node);
  return get_sibling(parent);
}

static void
rotate_left(struct rdg_range_node *node) {
  struct rdg_range_node *new_node = node->right;
  struct rdg_range_node *parent = get_parent(node);

  node->right = new_node->left;
  new_node->left = node;
  if (node->right != NULL) {
    node->right->parent = node;
  }

  if (parent != NULL) {
    if (node == parent->left) {
      parent->left = new_node;
    } else if (node == parent->right) {
      parent->right = new_node;
    }
  }
}

static void
repair(struct rdg_range_node *node) {
  if (get_parent(node) == NULL) {
    node->color = BLACK;
  } else if (get_parent(node)->color == BLACK) {
    // Do nothing
  } else if (get_uncle(node) != NULL && get_uncle(node)->color == RED) {
    get_parent(node)->color = BLACK;
    get_uncle(node)->color = BLACK;
    get_grand_parent(node)->color = RED;
    repair(get_grand_parent(node));
  } else {
    // TODO: Balance set
  }
}

static int
add(struct rdg_range_node *root,
    struct rdg_range_node *node) {
  int comparison = compare(root->value, node->value);
  int status = 0;
  if (root != NULL) {
    if (comparison > 0) {
      if (root->right != NULL) {
        status = add(root->right, node);
      } else {
        node->parent = root;
        root->right = node;
      }
    } else if (comparison < 0) {
      if (root->left != NULL) {
        status = add(root->left, node);
      } else {
        node->parent = root;
        root->left = node;
      }
    } else {
      status = 1;
      free(node);
    }
  }
  return status;
}

void rdg_range_append_atom(struct rdg_range* range, unsigned char one) {
  struct rdg_range_node *new_node = malloc(sizeof(struct rdg_range_node));
  if (new_node != NULL) {
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = one;
    new_node->color = RED;
    if (range->root != NULL) {
      if (add(range->root, new_node) == 0) {
        range->size += 1;
      }
    } else {
      range->root = new_node;
      range->size += 1;
    }
    repair(new_node);
  }
}

void rdg_range_free(struct rdg_range* range) {
  if (range) {
    if (range->root) {
      free_node(range->root);
    }
    free(range);
  }
}

static struct rdg_range_node*
get_minimum(struct rdg_range_node* node) {
  struct rdg_range_node* min = node;
  if (node != NULL) {
    if (node->left != NULL) {
      min = get_minimum(node->left);
    }
  }
  return min;
}

struct rdg_range_iterator* rdg_range_begin(struct rdg_range* range) {
  range->iterator.node = get_minimum(range->root);
  return &(range->iterator);
}

unsigned char rdg_range_get(const struct rdg_range_iterator* iterator) {
  if (iterator->node == NULL) {
    return 0;
  }
  return iterator->node->value;
}

static int
is_left_child(struct rdg_range_node* node) {
  if (node->parent == NULL || node == node->parent->left) {
    return 1;
  } else {
    return 0;
  }
}

static struct rdg_range_node*
next(struct rdg_range_node* node) {
  struct rdg_range_node* next;
  if (node->right != NULL) {
    return get_minimum(node->right);
  }
  while (!is_left_child(node)) {
    node = node->parent;
  }
  return node->parent;
}

int rdg_range_next(struct rdg_range_iterator* iterator) {
  int has_next = 0;
  if (iterator->node) {
    iterator->node = next(iterator->node);
    if (iterator->node != NULL) {
      has_next = 1;
    }
  }
  return has_next;
}
