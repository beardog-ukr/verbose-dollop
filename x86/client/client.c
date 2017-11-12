#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h> 

#include "client.h"

// ================================================================================================

int make_connect(int* sockfd_p, char* server_address, const int port)
{
    int sockfd =0;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("%s:%d::ERROR: Could not create socket %d:\"%s\"\n", 
               __func__, __LINE__, errno, strerror(errno));
        return ERR_CONNECT_SOCKET_CREATE;
    } 

    // int flags = fcntl(sockfd, F_GETFL, 0);
    // fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in serv_addr; 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, server_address, &serv_addr.sin_addr)<=0)
    {
        printf("%s:%d::ERROR: inet_pton error occured %d:\"%s\"\n", 
               __func__, __LINE__, errno, strerror(errno));
        return ERR_CONNECT_INET_PTON;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("%s:%d::ERROR: Connect Failed %d:\"%s\"\n", 
               __func__, __LINE__, errno, strerror(errno));
       return ERR_CONNECT_CONNECT;
    } 

    printf("%s:Connected\n", __func__);
    *sockfd_p = sockfd;

    return ERR_NO_ERR;
}

// ================================================================================================

int send_command(const int sockfd, char* command, size_t command_len)
{
    if (send(sockfd, command, command_len, 0) == -1) 
    {
      printf("%s:%d::ERROR: send\n", __func__, __LINE__);
      return ERR_SEND_COMMAND_SEND;
    }

    char rbuf[COMMAND_LEN_MAX];
    memset(rbuf, 0, sizeof(rbuf));

    int recv_result = recv(sockfd, rbuf, sizeof(rbuf), 0);
    printf("%s:%d:: received %d bytes\n", __func__, __LINE__, recv_result);
    if (recv_result > 0) 
    {
      rbuf[sizeof(rbuf)-1] = '\0';
    } 
    else 
    {
        if (recv_result < 0) 
        {
            printf("%s:%d::ERROR: recv\n", __func__, __LINE__);
            return ERR_SEND_COMMAND_RECV;
        }
        else 
        {
            printf("Server closed connection\n");
            return ERR_SEND_COMMAND_CLOSED;
        }
    }

    return ERR_NO_ERR;
}

// ================================================================================================

int make_disconnect()
{
    return ERR_NO_ERR;
}



