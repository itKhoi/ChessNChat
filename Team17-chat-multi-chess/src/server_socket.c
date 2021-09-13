//
// Created by entropy on 2/28/19.
//

#include "server_socket.h"

char* socket_handler(char* message)
{
    char* message_ret = malloc(sizeof(char) * BUFFER_LEN);
    for(int i = 0; i < BUFFER_LEN; i++)
        message_ret[i] = 0;

    if(strstr(message, "LOGIN") != NULL)
    {
        // LOGIN
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* username = tok;
        tok = strtok(NULL, ",");
        char* password = tok;
        int status = loginVerification(username, password);
        if(status > 0)
            message_ret = userId_int2str(status);
        else if(status == 0)
            return "0";
            else if(status == -1)
                return "-1";
                else if(status == -2)
                    return "EXCEPTION";

        return message_ret;
    } else if(strstr(message, "REGISTER") != NULL)
    {
        // REGISTER
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* username = tok;
        tok = strtok(NULL, ",");
        char* password = tok;
        int userId = createUser(username, password);
        message_ret = userId_int2str(userId);
        return message_ret;
    } else if(strstr(message, "GETNAME") != NULL)
    {
        // GETNAME,USERID
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* userId_str = tok;

        strcpy(message_ret, getUsername(userId_str2int(userId_str)));
        return message_ret;
    } else if(strstr(message, "QUEUE") != NULL)
    {
        // QUEUE,USERID,FROMID
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* userId_str = tok;
        tok = strtok(NULL, ",");
        char* from_id_i = tok;

        int userId = userId_str2int(userId_str);
        int* messageQueue = getMessageQueue(userId);
        int* curr = messageQueue;

        if(*curr == 0)
        {
            // the message queue is empty
            strcpy(message_ret, "-1");
            return message_ret;
        }

        while(*curr != 0)
        {
            char * message = malloc(100);
            message = getMessage(*curr);
            char* tok = strtok(message, ",");
            // printf("%s\n", tok);

            int from_id_int = userId_str2int(tok);
            int from_id_i_int = userId_str2int(from_id_i);

            if(from_id_i_int == from_id_int)
            {
                strcat(message_ret, userId_int2str(*curr));
                strcat(message_ret, ",");
            }

            curr++;
        }

        clearQueue(userId);

        if(message_ret[0] == 0)
        {
            strcpy(message_ret, "-1");
            return message_ret;
        }

        return message_ret;
    } else if(strstr(message, "MESSAGE") != NULL)
    {
        // MESSAGE,MESSAGEID
        char* tokk = strtok(message, ",");
        tokk = strtok(NULL, ",");
        char* messageId = tokk;

        char *msg = malloc(1000);

        msg = getMessage(userId_str2int(messageId));

        char* tok = strtok(msg, ",");
        tok = strtok(NULL, ",");

        char* msgn = tok;

        strcpy(message_ret, msgn);

        return message_ret;
    } else if(strstr(message, "SEND") != NULL)
    {
        // SEND,FROMID,TOID,MESSAGE
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* fromid_str = tok;
        tok = strtok(NULL, ",");
        char* toId_str = tok;
        tok = strtok(NULL, ",");
        char* message = tok;

        printf("From:%s\tTo:%s\n", fromid_str, toId_str);

        int ret = appendMessageQueue(userId_str2int(toId_str), userId_str2int(fromid_str), message);
        if(ret == 1)
            strcpy(message_ret, "1");
        else
            strcpy(message_ret, "0");
        return message_ret;
    } else if(strstr(message, "GETFRI") != NULL)
    {
        // GETFRI,USERID
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* userId = tok;

        int userId_int = userId_str2int(userId);
        int* fri_list = getFriendList(userId_int);

        int* curr = fri_list;
        while(*curr != 0)
        {
            strcat(message_ret, userId_int2str(*curr));
            strcat(message_ret, ",");
            curr++;
        }

        return message_ret;
    } else if(strstr(message, "ADDFRI") != NULL)
    {
        // ADDFRI,FROMID,FRIID
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* fromid_str = tok;
        tok = strtok(NULL, ",");
        char* friId_str = tok;

        printf("Add friend From:%s\tTo:%s\n", fromid_str, friId_str);

        int ret = addFriend(userId_str2int(fromid_str), userId_str2int(friId_str));

        if(ret == 1)
            strcpy(message_ret, "1");
        else
            strcpy(message_ret, "0");
        return message_ret;
    } else if(strstr(message, "DELETEFRI") != NULL)
    {
        // DELETEFRI,FROMID,FRIID
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* fromid_str = tok;
        tok = strtok(NULL, ",");
        char* friId_str = tok;

        printf("Delete friend From:%s\tTo:%s\n", fromid_str, friId_str);

        int userId = userId_str2int(fromid_str);
        int friId = userId_str2int(friId_str);
        int * fri_list = getFriendList(userId);

        // delete all the friend first
        deleteAllFriend(userId);

        // add friends back then
        int* curr = fri_list;
        while(*curr != 0)
        {
            if(*curr != friId)
            {
                // this friend is not supposed to be deleted
                addFriend(userId, *curr);
            }
            curr++;
        }

        strcpy(message_ret, "1");
        return message_ret;
    } else if(strstr(message, "GETSTAT") != NULL)
    {
        // GETSTAT,USERID
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* userId_str = tok;

        int userId = userId_str2int(userId_str);

        strcpy(message_ret, userId_int2str(getStatus(userId)));

        return message_ret;
    } else if(strstr(message, "SETSTAT") != NULL)
    {
        // SETSTAT,USERID,STATUS
        char* tok = strtok(message, ",");
        tok = strtok(NULL, ",");
        char* userId = tok;
        tok = strtok(NULL, ",");
        char* status = tok;

        int ret = setStatus(userId_str2int(userId), userId_str2int(status));

        strcpy(message_ret, userId_int2str(ret));

        return message_ret;
    } else
    {
        // EXCEPTION!
        strcpy(message_ret, "EXCEPTION");
        return message_ret;
    }
}


void* socketThread(void* arg)
{
    int sockid = *(int*) arg;

    char recv_buffer [BUFFER_LEN];
    char send_buffer [BUFFER_LEN];

    recv(sockid, recv_buffer, BUFFER_LEN, 0);

#ifdef DEBUG
    printf("Received From socket %d : %s\n", sockid, recv_buffer);
    fflush(stdout);
#endif

    strcpy(send_buffer, socket_handler(recv_buffer));
    send(sockid, send_buffer, BUFFER_LEN, 0);
    close(sockid);
    return NULL;
}


void entry_point(int port)
{
    printf("Server Started!\n");
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    if(sockid == 0)
        printf("Cannot Open Port!!\n");
    int bind_status = bind(sockid, (struct sockaddr *)&address, sizeof(address));
#ifdef DEBUG
    printf("Bind Status:%d\n", bind_status);
#endif
    if(bind_status != 0)
    {
        printf("Cannot Bind to Port! Try another port.");
        return;
    }
    listen(sockid, MAXPENDING);

    pthread_t tid[MAX_USERS + 10];
    int i = 0;
    while(1)
    {
        int new_socket = accept(sockid, NULL, NULL);
        // printf("new_socket:%d\n", new_socket);
        // fflush(stdout);
        pthread_create(&tid[i], NULL, socketThread, &new_socket);
        // printf("%d\n", status);
        // fflush(stdout);

        if( i >= MAX_USERS)
        {
            i = 0;
            while(i < MAX_USERS)
            {
                pthread_join(tid[i++], NULL);
            }
            i = 0;
        }
    }
}

// For the command line argument, you may want to do ./server_socketTest -p 1717
#ifdef DEBUG
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
    entry_point(port);
}
#endif
