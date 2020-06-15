#include <malloc.h>
#include <inttypes.h>
#include "include/rvm.h"
#include <mruby.h>
#include <mruby/irep.h>
#include <libgen.h>

int main(int argc, char **argv) {
	uint16_t fn_size = 255;
	char *filename = (char *) malloc(sizeof(char) * fn_size);
	if (argc > 1) {
		if (sizeof(argv[1]) > fn_size) {
			fn_size = sizeof(argv[1]);
			filename = realloc(filename, sizeof(char) * fn_size);
			if (!filename) {
				return -1;
			}
		}
		filename = argv[1];

		mrb_state *mrb = mrb_open();
		if (!mrb) {
			return -1;
		}

		rvm_lstl(mrb, NULL, dirname(filename));
		mrbi_ld_file(mrb, filename);
		mrbi_ld_file(mrb, "core.rb");
		if (mrb->exc) {
			mrb_print_error(mrb);
		}
		mrb_close(mrb);
	}
	return 0;
}