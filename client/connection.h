#ifndef _CONNECTION_H
#define _CONNECTION_H

#define SRV_FILE "./server_ip"
#define TCP_PORT 6666

#define MAX_IP 20

#define BUF_SIZE 1000


/*
 * Description: Get chat server information.
 * 
 */
int server_info_get(struct sockaddr_in *server_info);



/*
 * Description: Connect to chat server.
 * 
 */
int server_connect(struct sockaddr_in *server_info);


#endif
