#include "rdg.h"

#include <dirent.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

static void rdg_protocol_write(const unsigned char *data, size_t size) {
  uint64_t protocol_size = __builtin_bswap64(size);
  fwrite(&protocol_size, sizeof(uint64_t), 1, stdout);
  fwrite(data, size, 1, stdout);
}

static int rdg_generate_stdout(struct rdg* rdg) {
  unsigned char* data = NULL;
  size_t size = 0;
  while(rdg_generate(&data, &size, rdg)) {
    rdg_protocol_write(data, size);
  }
  rdg_free(rdg);
  return EXIT_SUCCESS;
}

static int rdg_generate_files(const char* dirname, struct rdg* rdg) {
  char filename[255];
  FILE *fp = NULL;
  DIR *dir = NULL;
  unsigned char* data = NULL;
  size_t size = 0;
  size_t counter = 0;
  if ((dir = opendir(dirname)) == NULL) {
    rdg_free(rdg);
    return EXIT_FAILURE;
  }
  closedir(dir);
    
  while(rdg_generate(&data, &size, rdg)) {
    counter++;
    snprintf(filename, 255, "%s/%lu", dirname, counter);
    if ((fp = fopen(filename, "wb")) == NULL) {
      (void) rdg_free(rdg);
      fprintf(stderr, "Failed to open new file: %s\n", filename);
      return EXIT_FAILURE;
    }
    
    if (fwrite(data, size, 1, fp) != 1) {
      (void) rdg_free(rdg);
      fprintf(stderr, "Failed to write generated data.\n");
      return EXIT_FAILURE;
    }
    (void) fclose(fp);
    (void) free(data);
  }
  printf("%lu file(s) created.\n", counter);
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  struct rdg* rdg = NULL;
  int rc = EXIT_SUCCESS;
  size_t counter = 0;
  char *line = NULL;
  size_t size = 0;

  if (argc > 3) {
    fprintf(stderr, "Usage: rdg [ <expression> <directory> ]");
    exit(1);
  }


  if (argc > 1) {
    rdg = rdg_new(argv[1]);

    if (rdg == NULL) {
      return EXIT_FAILURE;
    }
    
    if (argc == 2) {
      return rdg_generate_stdout(rdg);
    } else if (argc == 3) {
      return rdg_generate_files(argv[2], rdg);
    }
  } else {
    while (getline(&line, &size, stdin) != -1) {
      line[strlen(line) - 1] = 0;
      rdg = rdg_new(line);
      if (rdg) {
        if (rdg_generate_stdout(rdg) == EXIT_FAILURE) {
          return EXIT_FAILURE;
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
