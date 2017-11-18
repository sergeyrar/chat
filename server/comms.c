#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>  
#include <errno.h>
#include <pthread.h>
#include <assert.h>

#include "comms.h"
#include "error.h"

/* Local Functions */
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
	
	assert(0);
	return NULL;
}




int server_start(connection_t *chat_conn)
{
	int i=0;
	pthread_t recv_thread;
	pthread_t send_thread;
	
	chat_conn->listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    chat_conn->serv_addr.sin_family = AF_INET;
    chat_conn->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    chat_conn->serv_addr.sin_port = htons(TCP_PORT); 
    
    bind(chat_conn->listenfd, (struct sockaddr*)&chat_conn->serv_addr, sizeof(chat_conn->serv_addr)); 
    listen(chat_conn->listenfd, CLIENT_MAX); 
    
	if (pthread_create(&send_thread, NULL, send_to_clients_thread, chat_conn) != 0)
	{
		perror("send pthread creation failed\n");
	}
		
	if (pthread_create(&recv_thread, NULL, rcv_from_clients_thread, chat_conn) != 0)
	{
		perror("rcv pthread creation failed\n");
	}
    
	while(1)
    {
        chat_conn->connfd[i] = accept(chat_conn->listenfd, (struct sockaddr*)NULL, NULL); 
        i++;
        usleep(1000000);
    }
    
}



 
 

