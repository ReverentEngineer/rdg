#include "rdg.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>

int main() {
  struct rdg *rdg = NULL;
  
  rdg = rdg_new("test[123]");
  assert(rdg != NULL);
  assert(rdg_permutations(rdg) == 3);
  (void) rdg_free(rdg);

  rdg = rdg_new("test[123][abc]");
  assert(rdg != NULL);
  assert(rdg_permutations(rdg) == 9);
  (void) rdg_free(rdg);

  return 0;
}
