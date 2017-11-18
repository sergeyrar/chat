#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>

#include "comms.h"
#include "error.h"




void * rcv_from_clients_thread(void * chat_conn_ptr)
{
	int len;
	connection_t *chat_conn = (connection_t *)chat_conn_ptr;
	
	while (1)
	{
		for (int i = 0; i < CLIENT_MAX; i++)
		{
			if (chat_conn->connfd[i] != 0)
			{	//should probably be NON-blocking recv!
				if ((len = recv(chat_conn->connfd[i], chat_conn->chat_buff.data, BUF_MAX, 0)) < 0)
				{
					perror("recv failed");
					return NULL;
				}
				
				chat_conn->chat_buff.buf_len += len;
			}
		}
		
	}
	
	assert(0);
	return NULL;

}


void * send_to_clients_thread(void * chat_conn_ptr)
{
	int len;
	connection_t *chat_conn = (connection_t *)chat_conn_ptr;
	
	while (1)
	{
		if (chat_conn->chat_buff.buf_len > 0)
		{
			for (int i = 0; i < CLIENT_MAX; i++)
			{
				if (chat_conn->connfd[i] != 0)
				{
						if ((len = send(chat_conn->connfd[i], chat_conn->chat_buff.data, chat_conn->chat_buff.buf_len, 0)) < 0)
						{
							perror("send failed");
							return NULL;
						}
				}
			}
			
			chat_conn->chat_buff.buf_len = 0;
		}
	}
	
	assert(0);
	return NULL;
}


int main(int argc, char *argv[])
{
	int rv = OK;
	pthread_t recv_thread;
	pthread_t send_thread;
	
	connection_t chat_conn;
	memset(&chat_conn, 0, sizeof(connection_t));
	
	if (pthread_create(&send_thread, NULL, send_to_clients_thread, &chat_conn) != 0)
	{
		perror("send pthread creation failed\n");
	}
		
		
	if (pthread_create(&recv_thread, NULL, rcv_from_clients_thread, &chat_conn) != 0)
	{
		perror("rcv pthread creation failed\n");
	}
	
	
	if ((rv = server_start(&chat_conn)) != OK)
	{
		print_error(rv, "server start error");
		return rv;
	}
	
	
	return rv;
}
