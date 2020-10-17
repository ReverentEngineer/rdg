#include "rdg.h"

#include <dirent.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <math.h>

static int rdg_generate_stdout(struct rdg* rdg) {
  const unsigned char* data = NULL;
  size_t size = 0;

  fputc(0x30, stdout);
  fputc(0x80, stdout);
  
  while(rdg_generate(&data, &size, rdg)) {
    fputc(0x04, stdout);
    if (size < 128) {
      fputc(size & 0x7f, stdout);
    } else {
      int bits = ceil(log2(size));
      int bytes = (bits % 8 == 0) ? (bits / 8) : ((bits / 8) + 1);
      int i = bytes - 1;
      for (; i >= 0; i -= 1) {
        uint8_t byte = *(((uint8_t*)&size) + i);
        fputc(byte, stdout);
      }    
      fwrite(data, size, 1, stdout);
    }
    fwrite(data, size, 1, stdout);
  }
  fputc(0x00, stdout);
  fputc(0x00, stdout);
  rdg_free(rdg);
  return EXIT_SUCCESS;
}

static int rdg_generate_files(const char* dirname, struct rdg* rdg) {
  char filename[255];
  FILE *fp = NULL;
  DIR *dir = NULL;
  const unsigned char* data = NULL;
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
  }
  printf("%lu file(s) created.\n", counter);
  return EXIT_SUCCESS;
}

static void print_usage(void) {
  printf("usage: rdg [options] [<expression> <output_directory>]\n\n");
  printf("options:\n");
  printf("   --%-10s %s\n", "version", "Print version and exit");
  printf("   --%-10s %s\n", "help", "Print usage information and exit");
}

int main(int argc, char* argv[]) {
  struct rdg* rdg = NULL;
  int rc = EXIT_SUCCESS;
  size_t counter = 0;
  char *line = NULL;
  size_t size = 0;
  int c = 0;
  static int help = 0;
  static int version = 0;
  int option_index = 0;

  while (1) {
    static struct option long_options[] = {
      {"help", no_argument, &help, 1},
      {"version", no_argument, &version, 1},
      {0, 0, 0, 0}
    };
    
    c = getopt_long(argc, argv, "", long_options, &option_index);

    if (c == -1)
      break;
  
    switch (c) {
      case '?':
        print_usage();
        return EXIT_FAILURE;
        break;
      default:
        break;
    }
  }

  if (help) {
    print_usage();
    return EXIT_SUCCESS;
  }

  if (version) {
    printf("rdg version %s\n", rdg_get_version()); 
    return EXIT_SUCCESS;
  }


  if ((argc - optind) > 3) {
    print_usage();
    return EXIT_FAILURE;
  }


  if ((argc - optind) > 0) {
    rdg = rdg_new(argv[optind]);

    if (rdg == NULL) {
      return EXIT_FAILURE;
    }
    
    if (argc == 2) {
      return rdg_generate_stdout(rdg);
    } else if (argc == 3) {
      return rdg_generate_files(argv[optind + 1], rdg);
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
