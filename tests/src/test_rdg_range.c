#include "rdg_range.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>

int main() {
  struct rdg_range *range1 = NULL, *range2 = NULL;
  struct rdg_range_iterator *it = NULL;
  unsigned char value;
  unsigned char expected = 0;
  int i = 0;
  range1 = rdg_range_new();
  assert(range1 != NULL);
  assert(rdg_range_permutations(range1) == 0);
  (void) rdg_range_append_atom(range1, 'A');
  assert(rdg_range_permutations(range1) == 1);
  (void) rdg_range_append_atom(range1, 'B');
  assert(rdg_range_permutations(range1) == 2);
  (void) rdg_range_append_atom(range1, 'B');
  assert(rdg_range_permutations(range1) == 2);
  range2 = rdg_range_new_inclusive('a', 'z');
  assert(rdg_range_permutations(range2) == 26);
  it = rdg_range_begin(range2);
  assert(it != NULL);
  expected = 'a';
  for (; i < 25; i++) {
    value = rdg_range_get(it);
    assert((expected + i) == value);
    assert(rdg_range_next(it));
  }
  assert(!rdg_range_next(it));
  (void) rdg_range_append(range1, range2);
  assert(rdg_range_permutations(range1) == 28);
  rdg_range_free(range1);
  rdg_range_free(range2);
  return 0;
}
