#include <stdio.h>

#include "actions.h"
#include "client.h"


int init(int* sfd)
{
    char sa[] = "127.0.0.1";
    int port=9633;

    int result = make_connect(sfd, sa, port);
    if (ERR_NO_ERR != result)
    {
        printf("%s:%d::ERROR: failed to connect to %s:%d\n",
               __func__, __LINE__, sa, port);
    }

    return result;
}

int send_first_command(const int sfd)
{
    char command[] = "First Command";
    
    int result = send_command(sfd, command, sizeof(command));
    if (ERR_NO_ERR != result)
    {
        printf("%s:%d::ERROR: failed to send (%s)\n",
               __func__, __LINE__, command);
    }

    return result;
}

int send_second_command(const int sfd)
{
    char command[] = "Second Command";
    
    int result = send_command(sfd, command, sizeof(command));
    if (ERR_NO_ERR != result)
    {
        printf("%s:%d::ERROR: failed to send (%s)\n",
               __func__, __LINE__, command);
    }

    return result;
}