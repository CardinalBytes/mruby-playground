#ifndef RVM_H
#define RVM_H
#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/irep.h>

#define MAX_BUFFER 4096 * 1000

typedef enum { BigEndian, LittleEndian } endianess_t;

endianess_t rvm_det_endianess();
uint8_t *rvm_load_binary(const char *path, uint8_t *block);
uint64_t rvm_ingest_bytes(uint8_t *block, uint64_t to_ingest, FILE *from);
uint8_t *rvm_bytes_to_program(uint8_t *block);
static mrb_value rvm_loadb(mrb_state *mrb, mrb_value self);

int rvm_lstl(mrb_state *mrb, const char *std_path, const char *cr_bpat);

#endif
