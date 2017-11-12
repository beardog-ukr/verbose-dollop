#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "server.h"

int init_server(int* sockfd_p)
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // int flags = fcntl(sockfd, F_GETFL, 0);
    // fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in serv_addr; 
    memset(&serv_addr, '0', sizeof(serv_addr));    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9633); 

    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(sockfd, 10); 

    *sockfd_p = sockfd;

    return 0;
}

int get_connection(const int sfd, int* wfd)
{
    *wfd = accept(sfd, (struct sockaddr*)NULL, NULL); 

    return 0;
}

int process_command(const int wfd)
{
    char rbuf[COMMAND_LEN_MAX];
    memset(rbuf, 0, sizeof(rbuf));

    int recv_result = recv(wfd, rbuf, sizeof(rbuf), 0);
    if (recv_result > 0) 
    {
      rbuf[sizeof(rbuf)-1] = '\0';
      printf("=== Command: %s ===\n", rbuf);
    } 
    else 
    {
        if (recv_result < 0) 
        {
            printf("%s:%d::ERROR: recv\n", __func__, __LINE__);
            return 1;
        }
        else 
        {
            printf("Client closed connection\n");
            return 1;
        }
    }

    char server_resp[] = "Server responce";
    if (send(wfd, server_resp, sizeof(server_resp), 0) == -1) 
    //if (send(wfd, rbuf, sizeof(rbuf), 0) == -1) 
    {
      printf("%s:%d::ERROR: send\n", __func__, __LINE__);
      return 1;
    }

    return 0;
}

