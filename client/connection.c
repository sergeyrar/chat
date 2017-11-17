#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "connection.h"
#include "error.h"

/* LOCAL FUNCTIONS */
static err_code_t ip_address_get(struct in_addr *srv_ip)
{
	int rv = OK;
	
	char server_ip[MAX_IP];
	FILE *server_file = fopen(SRV_FILE, "r");	
	assert(server_file != NULL);
	
	if (fscanf(server_file, "%s", server_ip) == EOF)
	{
		perror("failed to get ip address from file");		
		return ERROR;
	}
	
	if (!inet_aton(server_ip, srv_ip))
	{
		fprintf(stderr, "Failed to convert IP address");
		return ERROR;
	}
		
	printf("got server IP - %u.%u.%u.%u\n",
	*(unsigned char *)srv_ip, *((unsigned char *)(srv_ip) + 1),
	*((unsigned char *)(srv_ip) + 2), *((unsigned char *)(srv_ip) + 3));
	
	fclose(server_file);
	
	return rv;
}

static int server_info_get(struct sockaddr_in *server_info)
{
	int rv = OK;
	
	if ((rv = ip_address_get(&server_info->sin_addr)) != OK)
	{
		print_error(rv, "ip address get error");
		return rv;
	}
	
	server_info->sin_family = AF_INET;
	server_info->sin_port = htons(TCP_PORT);
	

	return rv;
}





void * rcv_from_srv_thread(void * sock_fd_ptr)
{
	char recv_buf[BUF_SIZE] = {};
	int len = 0;
	int sock_fd = *(int *)sock_fd_ptr;
	
	
	while (1)
	{
		if ((len = recv(sock_fd, recv_buf, BUF_SIZE, 0)) < 0)
		{
			perror("recv failed");
			return NULL;
		}
		
		recv_buf[len] = '\0';
		printf("%s", recv_buf);
		
	}
	
	assert(0);
	return NULL;

}

void * send_to_srv_thread(void * sock_fd_ptr)
{
	char send_buf[BUF_SIZE] = {};
	int len;
	int sock_fd = *(int *)sock_fd_ptr;
	
	// stdout > /dev/null
	do
	{
		fgets(send_buf, BUF_SIZE, stdin);
		
		if ((len = send(sock_fd, send_buf, strlen(send_buf), 0)) < 0)
		{
			perror("send failed");
			return NULL;
		}
		
	} while(1);
	
	assert(0);
	return NULL;
}


static int server_connect(struct sockaddr_in *server_info)
{
	int rv = OK;
	int sock_fd;
	
	
	pthread_t recv_thread;
	pthread_t send_thread;
	
	
	
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Failed to creade socket");
	}
	
	if (connect(sock_fd, (struct sockaddr *)server_info, sizeof(*server_info)) < 0)
    {
       perror("Failed to connect to remote server\n");
       return ERROR;
    } 
	
	
	if (pthread_create(&send_thread, NULL, send_to_srv_thread, &sock_fd) != 0)
	{
		perror("send pthread creation failed\n");
	}
		
	if (pthread_create(&recv_thread, NULL, rcv_from_srv_thread, &sock_fd) != 0)
	{
		perror("rcv pthread creation failed\n");
	}
	
	while(1)
	{
		usleep(1000000);
	}
	
	
	return rv;
}


/* EXPORTED FUNCTIONS */
int server_setup_connection(const char *client_name)
{
	int rv = OK;
	struct sockaddr_in server_info = {};
	//~ memset(&server_info, 0, sizeof(struct sockaddr_in));
	
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
	
	
	
	return rv;

}
