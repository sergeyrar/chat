#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "connection.h"
#include "error.h"






int main(int argc, char *argv[])
{
	int rv;
	
	if ((rv = server_setup_connection()) != OK)
	{
		print_error(rv, "server setup connection error");
		return rv;
	}

	
	return OK;
}
