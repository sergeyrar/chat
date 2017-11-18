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
#include <fcntl.h>

#include "comms.h"
#include "error.h"



int server_start(connection_t *chat_conn)
{
	int i=0;
	
	chat_conn->listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    chat_conn->serv_addr.sin_family = AF_INET;
    chat_conn->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    chat_conn->serv_addr.sin_port = htons(TCP_PORT); 
    
    bind(chat_conn->listenfd, (struct sockaddr*)&chat_conn->serv_addr, sizeof(chat_conn->serv_addr)); 
    listen(chat_conn->listenfd, CLIENT_MAX); 
    
	while(i < CLIENT_MAX)
    {
        chat_conn->connfd[i] = accept(chat_conn->listenfd, (struct sockaddr*)NULL, NULL);
        
		// Convert to non-blocking TCP socket.
		if (fcntl(chat_conn->connfd[i], F_SETFL, fcntl(chat_conn->connfd[i], F_GETFL) | O_NONBLOCK) < 0) 
		{
			perror("failed to convert socket to non-blocking");
		} 

#ifdef DEBUG_FLAG
        printf("Accepted a new connection %d\n", i);
#endif
        i++;
    }
    
    while(1) usleep(1000000);
    
}



 
 

