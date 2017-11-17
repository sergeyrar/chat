#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "connection.h"
#include "error.h"


#define MAX_NAME 50




int get_client_name(char *client_name)
{
	char *test;
	test = fgets(client_name, MAX_NAME, stdin);
	assert(test != NULL);
	
	client_name[strlen(client_name) - 1] = '\0';
	
	return OK;
}



int main(int argc, char *argv[])
{
	int rv;
	char client_name[MAX_NAME];
	
	rv = get_client_name(client_name);
	check_error(rv, "get_client_name failed");
	
	rv = connect_to_server();
	check_error(rv, "connect_to_server failed");
	
		
	
	return OK;
}
