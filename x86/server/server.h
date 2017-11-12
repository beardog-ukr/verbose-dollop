#ifndef __server__h__
#define __server__h__

#define COMMAND_LEN_MAX 1024

int init_server(int* sockfd_p);

int get_connection(const int sfd, int* wfd);

int process_command(const int wfd);

#endif