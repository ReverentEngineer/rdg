#include "rdg_atom.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(rdg_byte_to_atom("\\x00") == 0);
  assert(rdg_byte_to_atom("\\xff") == 0xff);
  assert(rdg_byte_to_atom("\\xf0") == 0xf0);
  assert(rdg_byte_to_atom("\\x0f") == 0x0f);
  assert(rdg_byte_to_atom("\\x01") == 0x01);
  assert(rdg_byte_to_atom("\\x10") == 0x10);
  return 0;
}
