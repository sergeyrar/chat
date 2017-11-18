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
    
	while(1)
    {
        chat_conn->connfd[i] = accept(chat_conn->listenfd, (struct sockaddr*)NULL, NULL); 
        i++;
        usleep(1000000);
    }
    
}



 
 

