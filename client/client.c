#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "connection.h"
#include "error.h"

#define MAX_NAME 50

char client_name[MAX_NAME];


static int client_name_get(char *client_name)
{
	int rv = OK;
	
	printf("What is your name? \n");
	char *test;
	test = fgets(client_name, MAX_NAME, stdin);
	assert(test != NULL);
	
	printf("length of name is : %lu\n", strlen(client_name));
	
	client_name[strlen(client_name) - 1] = ':';
	
	
	
	return rv;
}



int main(int argc, char *argv[])
{
	int rv;
	struct sockaddr_in server_info = {};
	
	if ((rv = client_name_get(client_name)) != OK)
	{
		print_error(rv, "client get name error");
		return rv;
	}
	
	
	if ((rv = server_info_get(&server_info)) != OK)
	{
		print_error(rv, "server info get error");
		return rv;
	}
	
	
	if ((rv = server_connect(&server_info)) != OK)
	{
		print_error(rv, "server connect error");
		return rv;
	}
	
	
	return OK;
}
