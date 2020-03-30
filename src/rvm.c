#include "rvm.h"
#include "consts.h"

uint8_t *open_binary(const char *path, uint8_t *block) {
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
uint8_t *rvm_bytes_to_program(const uint8_t *block) {
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

  uint8_t *program = (uint8_t *) malloc(sizeof(uint8_t) * program_size.i);
  if (!program) {
    return 0;
  }

  for (int i = 0; i < program_size.i; i++) {
    program[i] = block[i];
  }

  return program;
}

endianess_t rvm_det_endianess() {
  union {
    uint8_t buff[4];
    uint32_t i;
  } det;

  det.i = 0x01020304;
  return (det.buff[0] == 0x01) ? BigEndian : LittleEndian;
}

int load_std_lib(mrb_state *mrb, const char *std_path) {
  mrb_define_const(mrb, mrb->kernel_module, "STD_PATH", mrb_str_new_cstr(mrb, (std_path != NULL) ? std_path : "std"));

}
