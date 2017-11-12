#ifndef __client_h__
#define __client_h__

#include <stddef.h>

#define COMMAND_LEN_MAX 1024

enum {
    ERR_NO_ERR =0,
    ERR_CONNECT_SOCKET_CREATE = 1,
    ERR_CONNECT_INET_PTON,
    ERR_CONNECT_CONNECT,

    ERR_SEND_COMMAND_SEND,
    ERR_SEND_COMMAND_RECV,
    ERR_SEND_COMMAND_CLOSED

} client_error_codes;

int make_connect(int* sockfd_p, char* server_address, const int port);
int send_command(const int sockfd, char* command, size_t command_len);
int make_disconnect();

#endif