#include "include/rvm.h"
#include "consts.h"
#include <unistd.h>
#include <math.h>

endianess_t rvm_det_endianess()
{
	union {
	    uint8_t buff[4];
	    uint32_t i;
	} det;

	det.i = 0x01020304;
	return (det.buff[0] == 0x01) ? BigEndian : LittleEndian;
}

void mrbi_ld_bin(mrb_state *mrb, char *bytes)
{

	mrb_load_irep(mrb, bytes);
}

void mrbi_ld_src(mrb_state *mrb, char *str)
{
	mrb_load_string(mrb, str);
}

int ftb(FILE *fp, char **buffer) {
	size_t len;
	/*
	 * Determine the file size */
	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	rewind(fp);

	*buffer = malloc(len);
	if (!*buffer)
		return 0;

	fread((void *)*buffer, sizeof(char), len, fp);
	if (*buffer == 0)
		return 0;
	return 1;
}

int assert_fsig(char *bytes)
{
	uint8_t sig[8];
	int i;
	for (i = 0; i < sizeof(irep_sig); i++) {
		if (bytes[i] == irep_sig[i])
			continue;
		else
			return -1;
	}
	return 0;
}

void mrbi_ld_file(mrb_state *mrb, const char *fn)
{
	FILE *fp;
	char *code_buff;
	fp = fopen(fn, "rb");
	if (!fp)
		return;

	ftb(fp, &code_buff);
	if (!code_buff)
		return;

	if (assert_fsig(code_buff) == 0)
		mrbi_ld_bin(mrb, code_buff);
	else
		mrbi_ld_src(mrb, code_buff);
}

mrb_value mrbi_cout(mrb_state *mrb, mrb_value self)
{
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

mrb_value mrbi_degtorad(mrb_state *mrb, mrb_value self)
{
	mrb_float arg = (double_t)0.0;
	mrb_float ret;

	mrb_get_args(mrb, "f", &arg);
	ret = arg * M_PI / 180.00;
	return mrb_float_value(mrb, ret);
}

mrb_value mrbi_radtodeg(mrb_state *mrb, mrb_value self)
{
	mrb_float arg = (double_t)0.0;
	mrb_float ret;

	mrb_get_args(mrb, "f", &arg);
	ret = arg * 180.00 / M_PI;
	return mrb_float_value(mrb, ret);
}

mrb_value mrbi_load(mrb_state *mrb, mrb_value self)
{
	mrb_value fn = mrb_nil_value();
	FILE *fp;
	size_t len;
	char *err_msg[255];
	char *fn_cstr;
	char *code_buff = 0;
	struct RClass *_class_internals = mrb_define_module(mrb, "Internals");

	mrb_get_args(mrb, "S", &fn);
	len = RSTRING_LEN(fn);
	fn_cstr = malloc(len);
	if (!fn_cstr) {
		snprintf((char *)err_msg, 255, "Memory allocation fault");
		goto load_fault;
	}
	if (access(fn_cstr, F_OK) == -1) {
		snprintf((char *)err_msg, 255, "Could not find file %s", fn_cstr);
		goto load_fault;
	}
	if (access(fn_cstr, R_OK) == -1) {
		snprintf((char *)err_msg, 255, "File %s is not readable", fn_cstr);
		goto load_fault;
	}

	fp = fopen(fn_cstr, "rb");
	if (!fp) {
		snprintf((char *)err_msg, 255, "Failed to open file %s", fn_cstr);
		goto load_fault;
	}
	if (!ftb(fp, &code_buff)) {
		snprintf((char *)err_msg, 255, "Memory allocation fault");
		goto load_fault;
	}

	/*
	 * Determining if the file is compiled bytecode or plain text
	 * by the signature */
	if (assert_fsig(code_buff) == 0)
		mrbi_ld_bin(mrb, code_buff);
	else
		mrbi_ld_src(mrb, code_buff);

	return mrb_bool_value(1);

    load_fault:
	free((void *)fn_cstr);
	free(code_buff);
	mrb_raise(mrb, _class_internals, (const char *)err_msg);
}

int rvm_lstl(mrb_state *mrb, const char *std_path, const char *cr_bpat)
{
	mrb_float pi = M_PI;
	mrb_float ec = M_E;
	mrb_define_const(mrb, mrb->kernel_module, "STD_PATH", mrb_str_new_cstr(mrb, (std_path != NULL) ? std_path
												       : "std"));
	mrb_define_const(mrb, mrb->kernel_module, "CR_BPAT", mrb_str_new_cstr(mrb, cr_bpat));
	struct RClass *_class_nmaths = mrb_define_module(mrb, "Math");
	struct RClass *_class_internals = mrb_define_module(mrb, "Internals");
	mrb_define_const(mrb, _class_nmaths, "PI", mrb_float_value(mrb, pi));
	mrb_define_const(mrb, _class_nmaths, "E", mrb_float_value(mrb, ec));
	mrb_define_class_method(mrb, _class_nmaths, "dtor", mrbi_degtorad, MRB_ARGS_REQ(1));
	mrb_define_class_method(mrb, _class_nmaths, "rtod", mrbi_radtodeg, MRB_ARGS_REQ(1));
	mrb_define_class_method(mrb, _class_internals, "load", mrbi_load, MRB_ARGS_REQ(1));
	mrb_define_class_method(mrb, _class_internals, "cout", mrbi_cout, MRB_ARGS_REQ(1));
	return 0;
}
