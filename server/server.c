#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "comms.h"
#include "error.h"





int main(int argc, char *argv[])
{
	int rv = OK;
	connection_t chat_conn;
	memset(&chat_conn, 0, sizeof(connection_t));
	
	if ((rv = server_start(&chat_conn)) != OK)
	{
		print_error(rv, "server start error");
		return rv;
	}
	
	
	return rv;
}
