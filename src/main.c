#include "rdg.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char* argv[]) {
  struct rdg* rdg = NULL;
  unsigned char* data = NULL;
  size_t size = 0;
  int has_next = 0;

  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: rdg <expression> [ <directory> ]");
    exit(1);
  }

  rdg = rdg_new(argv[1]);
  if (rdg == NULL) {
    return EXIT_FAILURE;
  }
 
  if (argc == 2) {
    do {
      has_next = rdg_generate(&data, &size, rdg);
    
    } while (has_next);
  }

  free(rdg);
}
