//
// Created by entropy on 3/5/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "database.h"
#include "server_socket.h"
#include "socketTester.h"

char* get(char* command, int port)
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockid, (struct sockaddr *)&address, sizeof(address));
    send(sockid, command, strlen(command), 0);
    char* buffer = malloc(sizeof(char) * BUFFER_LEN);
    recv(sockid, buffer, BUFFER_LEN, 0);

    return buffer;
}

int main(int argc, char* argv[])
{
    int port = -1;
    sscanf(argv[2], "%d", &port);
    if(port <=0)
    {
        printf("Wrong Command Line argument!");
        return -1;
    }
    printf("The Port is %d.\n", port);

    while(1)
    {
        char send_buffer[256] = {0};
        printf(">");
        scanf("%s", send_buffer);
        printf("%s\n", get(send_buffer, port));
    }
    return 0;
}
