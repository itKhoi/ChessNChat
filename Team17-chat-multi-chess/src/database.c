//
// Created by entropy on 2/25/19.
//

#include "database.h"


int checkUserExist(int userId)
{
    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".usr");

    FILE* fp;

    fp = fopen(filename, "r");

    if(fp)
    {
        fclose(fp);
        return 1;
    }

    return 0;
}


int nextUserId()
{
    for(int i = 1; i <= 99999999; i++)
    {
        if(checkUserExist(i) == 0)
        {
            // This userId is not in use yet
            return i;
        }
    }
    return -1;
}


int createUser(char* username, char* password)
{
    FILE* fp, *fp2, *fp3;

    int userId = nextUserId();

    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".usr");

    char filename2 [30];
    strcpy(filename2, USER_DIR);
    strcat(filename2, userId_int2str(userId));
    strcat(filename2, ".fri");

    fp2 = fopen(filename2, "w");
    fclose(fp2);

    // generate .que file to avoid seg fault
    char filename3 [30];
    strcpy(filename3, CHAT_DIR);
    strcat(filename3, userId_int2str(userId));
    strcat(filename3, ".que");
    fp3 = fopen(filename3, "w");
    fclose(fp3);

    // printf("%s\n", filename);

    fp = fopen(filename, "w");

    fprintf(fp, "%s\n%s\n", username, password);

    fclose(fp);

    return userId;
}


int deleteUser(int userId)
{
    if(checkUserExist(userId) == 0)
        return 0;

    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".usr");

    int status = remove(filename);

    if(status == 0)
        return 1;
    else
        return -1;
}


int loginVerification(char* username, char* password)
{
    int * current = listAllUsers();
    while(*current != 0)
    {
        if(strcmp(username, getUsername(*current)) == 0)
        {
            // found the user with the specified username
            if(strcmp(password, getPassword(*current)) == 0)
            {
                // Verification Successful
                return *current;
            } else
            {
                return -1;
            }
        }

        current++;
    }

    return 0;
}


char* getUsername(int userId)
{
    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".usr");

    FILE* fp;
    fp = fopen(filename, "r");

    if(fp == 0)
    {
        return "-1";
    }

    char* username = malloc(sizeof(char) * 20);
    char password[20];

    fscanf(fp, "%s\n%s\n", username, password);

    fclose(fp);

    return username;
}


char* getPassword(int userId)
{
    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".usr");

    FILE* fp;
    fp = fopen(filename, "r");

    char username[20];
    char* password = malloc(sizeof(char) * 20);

    fscanf(fp, "%s\n%s\n", username, password);

    fclose(fp);

    return password;
}


char* userId_int2str(int userId)
{
    char *userId_str = malloc(sizeof(char) * 9);

    sprintf(userId_str, "%08d", userId);

    return userId_str;
}


int userId_str2int(char* userId)
{
    int userId_int;

    sscanf(userId, "%08d", &userId_int);

    return userId_int;
}


int* listAllUsers()
{
    int* userId_lst = malloc(sizeof(int) * 100);

    for(int i = 0; i < 100; i++)
        userId_lst[i] = 0;

    int k = 0;
    for(int i = 0; i <= 999; i++)
    {
        if(checkUserExist(i))
        {
            userId_lst[k] = i;
            k++;
        }
    }

    return userId_lst;
}


void printUserIdList(int* userIdLst)
{
    int* current = userIdLst;
    while(*current != 0)
    {
        printf("%d\n", *current);
        fflush(stdout);
        current ++;
    }
}


int addFriend(int userId, int friend_userId)
{
    int* curr = getFriendList(userId);
    while(*curr != 0)
    {
        if(*curr == friend_userId)
        {
            // duplicated friend id
            return 0;
        }
        curr++;
    }

    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".fri");

    FILE* fp;
    fp = fopen(filename, "a");

    fprintf(fp, "%d\n", friend_userId);

    fclose(fp);
    return 1;
}


int* getFriendList(int userId)
{
    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".fri");

    FILE* fp;
    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        // the file does not exist
        // returning NULL for no friends
        return NULL;
    }

    // Compute the length of the friend list
    int temp;
    int f;
    int* fri_lst = malloc(sizeof(int) * 100);
    int* curr = fri_lst;
    for(int  i = 0; i < 100; i ++)
    {
        *curr = 0;
        curr++;
    }
    curr = fri_lst;
    do{
        f = fscanf(fp, "%d\n", &temp);
        if(temp != 0)
        {
            *curr = temp;
            curr ++;
        }
    } while(f != EOF);

    curr --;
    *curr = 0;

    fclose(fp);

    return fri_lst;
}


int deleteAllFriend(int userId)
{
    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".fri");

    FILE* fp;
    fp = fopen(filename, "w");
    fclose(fp);

    return 1;
}


int setStatus(int userId, int status)
{
    if(checkUserExist(userId) == 0)
    {
        // the user does not exist
        return 0;
    }


    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".sta");

    FILE* fp;
    fp = fopen(filename, "w");

    fprintf(fp, "%d", status);

    fclose(fp);

    return 1;

}


int getStatus(int userId)
{
    if(checkUserExist(userId) == 0)
    {
        // the user does not exist
        return -1;
    }

    char filename [30];
    strcpy(filename, USER_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".sta");

    FILE* fp;
    fp = fopen(filename, "r");

    int status = -1;
    fscanf(fp, "%d", &status);

    fclose(fp);

    return status;
}


int checkMessageExist(int messageId)
{
    char filename [30];
    strcpy(filename, CHAT_DIR);
    strcat(filename, userId_int2str(messageId));
    strcat(filename, ".cht");

    FILE* fp;

    fp = fopen(filename, "r");

    if(fp)
    {
        fclose(fp);
        return 1;
    }

    return 0;
}


int nextMessageId()
{
    for(int i = 1; i <= 99999999; i++)
    {
        if(checkMessageExist(i) == 0)
        {
            // This userId is not in use yet
            return i;
        }
    }
    return -1;
}


int appendMessageQueue(int userId, int fromId, char* message)
{
    int messageId = nextMessageId();

    char filename [30];
    strcpy(filename, CHAT_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".que");

    FILE* queue_fp;
    queue_fp = fopen(filename, "a");

    strcpy(filename, CHAT_DIR);
    strcat(filename, userId_int2str(messageId));
    strcat(filename, ".cht");

    FILE* chat_fp;
    chat_fp = fopen(filename, "w");

    // create the file containing the message
    fprintf(chat_fp, "%s,%s", userId_int2str(fromId), message);

    // append the message id to the queue
    fprintf(queue_fp, "%d\n", messageId);

    fclose(queue_fp);
    fclose(chat_fp);

    return 1;
}


int* getMessageQueue(int userId)
{
    char filename [30];
    strcpy(filename, CHAT_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".que");

    FILE* fp;
    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        // the file does not exist
        // returning NULL for no pending message
        return NULL;
    }

    // Compute the length of the friend list
    int temp;
    int f;
    int* fri_lst = malloc(sizeof(int) * 100);
    int* curr = fri_lst;
    for(int  i = 0; i < 100; i ++)
    {
        *curr = 0;
        curr++;
    }
    curr = fri_lst;
    do{
        f = fscanf(fp, "%d\n", &temp);
        if(temp != 0)
        {
            *curr = temp;
            curr ++;
        }
    } while(f != EOF);

    curr --;
    *curr = 0;

    fclose(fp);

    return fri_lst;
}


char* getMessage(int messageId)
{
    char filename [30];
    strcpy(filename, CHAT_DIR);
    strcat(filename, userId_int2str(messageId));
    strcat(filename, ".cht");

    FILE* fp;
    fp = fopen(filename, "r");

    // The maximum length of a message is 200
    char* message = malloc(sizeof(char) * 200);
    fscanf(fp, "%s", message);

    return message;
}


int clearQueue(int userId)
{
    char filename [30];
    strcpy(filename, CHAT_DIR);
    strcat(filename, userId_int2str(userId));
    strcat(filename, ".que");

    fclose(fopen(filename, "w"));

    return 1;
}


#ifdef DEBUG

int main()
{
    int userId = loginVerification("En", "123");

    int* friend_list = getFriendList(userId);

    int* curr = friend_list;
    while(*curr != 0)
    {
        printf("%d\n", *curr);
        curr++;
    }

    return 0;
}

#endif
