#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"


char *err_code_msgs[MAX_ERROR] = {
	"OK",
	"ERROR"
};


void print_error(err_code_t err_code, const char *err_msg)
{
	assert(err_code <= ERROR && err_code >= OK);
	fprintf(stderr, "%s, error-code %d:%s\n", err_msg, err_code, err_code_msgs[err_code]);
}
