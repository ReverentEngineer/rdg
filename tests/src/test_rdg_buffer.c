#include "rdg_buffer.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static const unsigned char input1[] = "hello";
static const unsigned char input2[] = "world";
static const unsigned char output[] = "helloworld";

int main() {
  struct rdg_buffer* buffer = NULL;
  unsigned char* data = NULL;
  int size = 0;
  buffer = rdg_buffer_new();
  assert(buffer != NULL);
  (void) rdg_buffer_append(buffer, input1, 5);
  (void) rdg_buffer_append(buffer, input2, 5);
  
  assert(rdg_buffer_size(buffer) == 10);
  data = rdg_buffer_release(buffer);
  assert(memcmp(output, data, 10) == 0);
  free(data);
  return 0;
}
