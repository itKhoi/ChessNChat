#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>  
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <arpa/inet.h>   
#include <netinet/in.h>

int receive_file(int socket);
int send_file(int socket);


#endif