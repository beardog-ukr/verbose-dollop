#include <stdio.h>

#include "actions.h"


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("This is client app\n");

    int sockfd;

    int result = 0;
    
    result =init(&sockfd);
    if (0 != result)
    {
        printf("Error during initialization\n");
        return 1;
    }    


    result = send_first_command(sockfd);
    if (0 != result)
    {
        printf("Error with first command\n");
        return 1;
    }    

    result = send_second_command(sockfd);
    if (0 != result)
    {
        printf("Error with second command\n");
        return 1;
    }    

    printf("Client app finished\n");
}
