#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "error.h"




void check_error(err_codes_t err_code, const char *err_msg)
{
	
	char *err_code_msgs[MAX_ERROR] = {
		"OK",
		"ERROR"
	};

	if (errno)
	{
		perror(err_msg);
		exit(1);
	}
	else if(err_code)
	{
		fprintf(stderr, "%s: %s\n", err_msg, err_code_msgs[err_code]);
	}
	
}
