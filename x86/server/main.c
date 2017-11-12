#include <stdio.h>

#include "server.h"


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("This is server app\n");

    int sockfd;

    int result = 0;
    
    result =init_server(&sockfd);
    if (0 != result)
    {
        printf("Error during initialization\n");
        return 1;
    }    


    while(1)
    {
        int working_fd;
        result = get_connection(sockfd, &working_fd);
        if (0 != result)
        {
            printf("Error, failed to get connection\n");
            return 1;
        }    

        result = process_command(working_fd);
        if (0 != result)
        {
            printf("Error processing first command\n");
            return 1;
        }  
        
        result = process_command(working_fd);
        if (0 != result)
        {
            printf("Error processing second command\n");
            return 1;
        }  
    }

    printf("Client app finished\n");
}