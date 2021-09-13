#ifndef CHAT_H
#define CHAT_H

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
void error(const char *msg);
void FatalError(const char *Program, const char *ErrorMsg);
int main(int argc , char *argv[]);

#endif