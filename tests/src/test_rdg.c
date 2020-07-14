#include "rdg.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main() {
  struct rdg *rdg = NULL;
  unsigned char *data = NULL;
  size_t size = 0;
  
  rdg = rdg_new("test[1-3]");
  assert(rdg != NULL);
  assert(rdg_permutations(rdg) == 3);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 5);
  assert(data != NULL);
  assert(memcmp("test1", data, 5) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 5);
  assert(data != NULL);
  assert(memcmp("test2", data, 5) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 5);
  assert(data != NULL);
  assert(memcmp("test3", data, 5) == 0);
  free(data);
  assert(!rdg_generate(&data, &size, rdg));
  assert(data == NULL);
  assert(size == 0);
  (void) rdg_free(rdg);

  rdg = rdg_new("test[123][a-c]");
  assert(rdg != NULL);
  assert(rdg_permutations(rdg) == 9);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test1a", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test1b", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test1c", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test2a", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test2b", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test2c", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test3a", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test3b", data, 6) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(size == 6);
  assert(data != NULL);
  assert(memcmp("test3c", data, 6) == 0);
  free(data);
  assert(!rdg_generate(&data, &size, rdg));
  assert(data == NULL);
  assert(size == 0);
  (void) rdg_free(rdg);

  rdg = rdg_new("\\x00(\\x01|\\x02)\\x03");
  assert(rdg_generate(&data, &size, rdg));
  assert(data != NULL);
  assert(size == 3);
  assert(memcmp("\x00\x01\x03", data, 3) == 0);
  free(data);
  assert(rdg_generate(&data, &size, rdg));
  assert(data != NULL);
  assert(size == 3);
  assert(memcmp("\x00\x02\x03", data, 3) == 0);
  free(data);
  (void) rdg_free(rdg);

  rdg = rdg_new("\\x00\\x01\\x02");
  assert(rdg_generate(&data, &size, rdg));
  assert(data != NULL);
  assert(size == 3);
  assert(memcmp("\x00\x01\x02", data, 3) == 0);
  free(data);
  (void) rdg_free(rdg);

  return 0;
}
