//
// Created by entropy on 2/28/19.
//

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "database.h"

#define PORT 2333
#define MAXPENDING 1
#define BUFFER_LEN 256

#define MAX_USERS 60

/* The thread created for handling an individual socket request */
void* socketThread(void* arg);

/* The entry point of the socket server. For debugging usage*/
void entry_point();

/* Handles message from the client, the return of this function is the reply to the client */
char* socket_handler(char* message);

#endif //TEAM17_SERVER_SOCKET_H
