#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "connection.h"
#include "error.h"


#define MAX_NAME 50




int client_name_get(char *client_name)
{
	int rv = OK;
	
	char *test;
	test = fgets(client_name, MAX_NAME, stdin);
	assert(test != NULL);
	
	client_name[strlen(client_name) - 1] = '\0';
	
	return rv;
}



int main(int argc, char *argv[])
{
	int rv;
	char client_name[MAX_NAME];
	
	if ((rv = client_name_get(client_name)) != OK)
	{
		print_error(rv, "client get name error");
		return rv;
	}
	
	if ((rv = server_setup_connection(client_name)) != OK)
	{
		print_error(rv, "server setup connection error");
		return rv;
	}

	
	return OK;
}
