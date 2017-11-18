#ifndef _COMMS_H
#define _COMMS_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TCP_PORT 6666
#define CLIENT_MAX 10
#define BUF_MAX 1000


typedef struct chat_buff_s {
	char data[BUF_MAX];
	size_t buf_len;
}chat_buff_t;


typedef struct connection_s {
	
	struct sockaddr_in serv_addr; 
	int listenfd;
	int connfd[CLIENT_MAX];
	
/* will probably have to protect from simultaneous reads/writes somehow 
 * There will be two threads, one for recv and one for transmit operating on 
 * the same buffer.
 */
	chat_buff_t chat_buff;
}connection_t;



/*
 * Purpose: create a listen TCP socket and accept connections
 * 
 * 
 */

int server_start();

#endif
