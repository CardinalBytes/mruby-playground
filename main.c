#include <jemalloc/jemalloc.h>
#include <stdio.h>
#include <inttypes.h>
#include "rvm.h"
#include <mruby.h>
#include <mruby/irep.h>
#include <mruby/error.h>

/**
 * This is given in bytes, if the binary to load is larger than this the program will throw an error
 * */
#define MAX_BUFFER 4096

int main(int argc, char **argv) {
  uint16_t fn_size = 255;
  char *filename = (char *) malloc(sizeof(char) * fn_size);
  if (argc > 1) {
    if (sizeof(argv[1]) > fn_size) {
      fn_size = sizeof(argv[1]);
      filename = realloc(filename, sizeof(char) * fn_size);
      if (!filename) {
        return 1;
      }
    }
    filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (!fp) {
      printf("File: %s, does not exist\n", filename);
      return 1;
    }

    uint8_t *byte_buff = (uint8_t *) malloc(sizeof(uint8_t) * MAX_BUFFER);
    if (!byte_buff) {
      return 1;
    }

    uint64_t ingested = rvm_ingest_bytes(byte_buff, MAX_BUFFER, fp);
    uint8_t *program = rvm_bytes_to_program(byte_buff);
    if (!program) {
      printf("invalid irep\n");
      return 1;
    }

    free((void *) byte_buff);

    mrb_state *mrb = mrb_open();
    if (!mrb) {
      printf("Failed to initialize mruby\n");
      return -1;
    }

    mrb_load_irep(mrb, program);
    mrb_close(mrb);
  }
  return 0;
}