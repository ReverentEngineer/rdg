#include "rdg.hh"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#include <stdlib.h>

#include <stdexcept>

int main() {
  RDG rdg("[a-c][1-3]");
  assert(rdg.generate() == "a1");
  assert(rdg.generate() == "a2");
  assert(rdg.generate() == "a3");
  assert(rdg.generate() == "b1");
  assert(rdg.generate() == "b2");
  assert(rdg.generate() == "b3");
  assert(rdg.generate() == "c1");
  assert(rdg.generate() == "c2");
  assert(rdg.generate() == "c3");
  try {
    rdg.generate();
    assert(false); // An exception should be thrown
  } catch (const std::length_error& ex) {
    assert(true); // Not necessary, but just showing we intended this.
  }

  return EXIT_SUCCESS;
}
