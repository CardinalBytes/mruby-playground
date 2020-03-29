#include <jemalloc/jemalloc.h>
#include <stdio.h>
#include <inttypes.h>
#include <mruby.h>
#include <string.h>
#include <mruby/irep.h>

/**
 * This is given in bytes, if the binary to load is larger than this the program will throw an error
 * */
#define MAX_BUFFER 4096
const uint8_t irep_sig[8] =
        {
                0x52, 0x49, 0x54, 0x45,
                0x30, 0x30, 0x30, 0x36
        };


typedef enum {BigEndian, LittleEndian} endianess_t;

uint64_t ingest_bytes(uint8_t *block, uint64_t to_ingest, FILE *from);
uint8_t *bytes_to_program(const uint8_t *block);
endianess_t det_endianess();

int main(int argc, char **argv) {
    uint16_t fn_size = 255;
    char *filename = (char *)malloc(sizeof(char) * fn_size);
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

        uint8_t *byte_buff = (uint8_t *)malloc(sizeof(uint8_t) * MAX_BUFFER);
        if (!byte_buff) {
            return 1;
        }

        uint64_t ingested = ingest_bytes(byte_buff, MAX_BUFFER, fp);
        uint8_t *program = bytes_to_program(byte_buff);
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

uint64_t ingest_bytes(uint8_t * block, uint64_t to_ingest, FILE *from){
    size_t read = fread(block, sizeof(uint8_t), to_ingest, from);
    return read;
}

/**
 * This function validates a program contained in the block param and strips any extra bytes at the end
 * @param block
 * @return 1 if the parsing was successful 0 otherwise
 */
uint8_t *bytes_to_program(const uint8_t *block) {
    /**
     * the following code validates the signature
     */
     uint8_t file_sig[8] = {0,0,0,0,
                            0,0,0,0};
     for (int i = 0; i < 0x08; i++) {
         file_sig[i] = (uint8_t)block[i];
     }

     if (memcmp(file_sig, irep_sig, sizeof(file_sig)) != 0) {
         return 0;
     }

    endianess_t endianess = det_endianess();
    union {
        uint8_t buff[4];
        uint32_t i;
    } program_size;
    /**
     * If little endian read the bytes in reverse
     */
    if (endianess == 1){
        int i2 = 0;
        for (int i = 0x0D; i > 0x09; i--) {
            printf("%d\t%02X\n", i2, block[i]);
            program_size.buff[i2] = (uint8_t)block[i];
            i2++;
        }
    } else {
        int i2 = 0;
        for (int i = 0x0A; i < 0x0E; i++) {
            printf("%02X\n", block[i]);
            program_size.buff[i2] = block[i];
            i2++;
        }
    }

    printf("%d\n", program_size.i);

    uint8_t *program = (uint8_t *)malloc(sizeof(uint8_t) * program_size.i);
    if (!program) {
        return 0;
    }

    for (int i = 0; i < program_size.i; i++) {
        program[i] = block[i];
    }

    return program;
}

endianess_t det_endianess() {
    union {
        uint8_t buff[4];
        uint32_t i;
    } det;

    det.i = 0x01020304;
    return (det.buff[0] == 0x01) ? BigEndian : LittleEndian;
}