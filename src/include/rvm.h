#ifndef RVM_H
#define RVM_H
#include <stdio.h>
#include <malloc.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/irep.h>

typedef enum { BigEndian, LittleEndian } endianess_t;

endianess_t rvm_det_endianess();
void mrbi_ld_bin(mrb_state *mrb, char *bytes);
void mrbi_ld_src(mrb_state *mrb, char *str);
void mrbi_ld_file(mrb_state *mrb, const char *fn);

int rvm_lstl(mrb_state *mrb, const char *std_path, const char *cr_bpat);

#endif
