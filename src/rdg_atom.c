#include "rdg_atom.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char rdg_byte_to_atom(const char* byte) {
  unsigned char atom;
  if (byte[0] != '\\' || byte[1] != 'x' || strlen(byte) != 4) {
    abort();
  }
  sscanf(byte + 2, "%2hhx", &atom);
  return atom; 
}
