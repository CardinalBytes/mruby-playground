#ifndef RVM_H
#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <mruby.h>
#include <mruby/compile.h>
typedef enum { BigEndian, LittleEndian } endianess_t;

char *rvm_search_path;

endianess_t rvm_det_endianess();
uint64_t rvm_ingest_bytes(uint8_t *block, uint64_t to_ingest, FILE *from);
uint8_t *rvm_bytes_to_program(const uint8_t *block);
#define RVM_H

#endif
