#include "rvm.h"
#include "consts.h"

uint8_t *rvm_load_binary(const char *path, uint8_t *block) {
  FILE *fp = fopen(path, "r");
  if (!fp) {
    return 0;
  }
  if (!rvm_ingest_bytes(block, MAX_BUFFER, fp)) {
    return 0;
  }
  return rvm_bytes_to_program(block);
}

uint64_t rvm_ingest_bytes(uint8_t *block, uint64_t to_ingest, FILE *from) {
  size_t read = fread(block, sizeof(uint8_t), to_ingest, from);
  return read;
}

/**
 * This function validates a program contained in the block param and makes it so a program uses only the needed memory
 * @param block
 * @return 1 if the parsing was successful 0 otherwise
 */
uint8_t *rvm_bytes_to_program(uint8_t *block) {
  /**
   * the following code validates the signature
   */
  uint8_t file_sig[8] = {0, 0, 0, 0,
                         0, 0, 0, 0};
  for (int i = 0; i < 0x08; i++) {
    file_sig[i] = (uint8_t) block[i];
  }

  if (memcmp(file_sig, irep_sig, sizeof(file_sig)) != 0) {
    return 0;
  }

  endianess_t endianess = rvm_det_endianess();
  union {
    uint8_t buff[4];
    uint32_t i;
  } program_size;

  int i2 = 0;
  for (int i = 0x0A; i < 0x0E; i++) {
    program_size.buff[i2] = block[i];
    i2++;
  }

  if (endianess == 1) {
    program_size.i = ntohl(program_size.i);
  }

  uint8_t *program = malloc(sizeof(uint8_t) * program_size.i);
  if (!program) {
    return 0;
  }

  return memcpy(program, block, (size_t)program_size.i);
}

endianess_t rvm_det_endianess() {
  union {
    uint8_t buff[4];
    uint32_t i;
  } det;

  det.i = 0x01020304;
  return (det.buff[0] == 0x01) ? BigEndian : LittleEndian;
}

mrb_value rvm_cout(mrb_state *mrb, mrb_value self) {
  mrb_value arg = mrb_nil_value();
  char *msg;
  size_t len = 0;

  mrb_get_args(mrb, "S", &arg);
  len = RSTRING_LEN(arg);
  msg = malloc(len);
  if (!msg) {
    return self;
  }
  msg = memcpy((void *)msg, (void *)RSTRING_PTR(arg), len);
  printf("%s", msg);
  free((void *)msg);
  return self;
}

mrb_value rvm_loadb(mrb_state *mrb, mrb_value self) {
  mrb_bool res = 0;
  mrb_value arg = mrb_nil_value();
  const char *path;
  size_t len = 0;

  uint8_t *block = malloc(sizeof(uint8_t) * MAX_BUFFER);
  if (!block) {
    return mrb_bool_value(res);
  }

  mrb_get_args(mrb, "S", &arg);
  len = RSTRING_LEN(arg);
  path = malloc(len);
  path = memcpy((void *)path, (void *)RSTRING_PTR(arg), len);
  uint8_t *code = rvm_load_binary(path, block);
  if (!code) {
    return mrb_bool_value(res);
  }
  mrb_load_irep(mrb, code);
  free(block);
  free((void *)path);
  res = 1;
  return mrb_bool_value(res);
}

int rvm_lstl(mrb_state *mrb, const char *std_path, const char *cr_bpat) {
  mrb_define_const(mrb, mrb->kernel_module, "STD_PATH", mrb_str_new_cstr(mrb, (std_path != NULL) ? std_path : "std"));
  mrb_define_const(mrb, mrb->kernel_module, "CR_BPAT", mrb_str_new_cstr(mrb, cr_bpat));
  struct RClass *_class_native = mrb_define_module(mrb, "INative");
  mrb_define_class_method(mrb, _class_native, "load", rvm_loadb, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, _class_native, "cout", rvm_cout, MRB_ARGS_REQ(1));
  return 0;
}
