#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>


#include "connection.h"
#include "error.h"

#define MAX_IP 20


int connect_to_server()
{
	int rv = OK;
	
	struct sockaddr_in server_info;
	char server_ip[MAX_IP];
	FILE *server_file = fopen(SRV_FILE, "r");	
	assert(server_file != NULL);
	
	fscanf(server_file, "%s", server_ip);
	check_error(errno, "fscanf failed");
	
	inet_aton(server_ip, &server_info.sin_addr);

		
	printf("got server IP - %u.%u.%u.%u\n",
	*(unsigned char *)&server_info.sin_addr, *((unsigned char *)(&server_info.sin_addr) + 1),
	*((unsigned char *)(&server_info.sin_addr) + 2), *((unsigned char *)(&server_info.sin_addr) + 3));
	
	fclose(server_file);
	return rv;
}
