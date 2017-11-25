#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "comms.h"
#include "error.h"

pthread_mutex_t mutex;


void * rcv_from_clients_thread(void * chat_conn_ptr)
{
	int len = 0;
	connection_t *chat_conn = (connection_t *)chat_conn_ptr;
	
	while (1)
	{
		for (int i = 0; i < CLIENT_MAX; i++)
		{
			if (chat_conn->connfd[i] != 0)
			{	
				if ((len = recv(chat_conn->connfd[i], chat_conn->chat_buff.data, BUF_MAX, 0)) < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						continue;
					}
					perror("recv failed");
					return NULL;
				}
				//pthread_mutex_lock(&mutex);
				chat_conn->chat_buff.buf_len += len;
				//pthread_mutex_unlock(&mutex);
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
			//pthread_mutex_lock(&mutex);
			chat_conn->chat_buff.buf_len = 0;
			//pthread_mutex_unlock(&mutex);
		}
	}
	
	assert(0);
	return NULL;
}


static void daemon_fd_init()
{
	int fd = open("./server.log", O_WRONLY);
	
	if (fd < 0) perror("Failed to open file for writing");
	
	dup2(fd, 1);
	dup2(fd, 2);
	
	close(fd);
}


int main(int argc, char *argv[])
{
	int rv = OK;
	pthread_t recv_thread;
	pthread_t send_thread;
	connection_t chat_conn;
	pid_t pid;
	
	pid = fork();
	// check for fork error
	if (pid < 0) perror("Fork failed\n");
	//exit from parent process
	if (pid > 0) exit(0);
	
	// Now running as daemon in child process
	daemon_fd_init();

	memset(&chat_conn, 0, sizeof(connection_t));
	
	if (pthread_create(&send_thread, NULL, send_to_clients_thread, &chat_conn) != 0)
		perror("send pthread creation failed\n");	
		
	if (pthread_create(&recv_thread, NULL, rcv_from_clients_thread, &chat_conn) != 0)
		perror("rcv pthread creation failed\n");
	
	if ((rv = server_start(&chat_conn)) != OK)
	{
		print_error(rv, "server start error");
		return rv;
	}
	
	
	return rv;
}
