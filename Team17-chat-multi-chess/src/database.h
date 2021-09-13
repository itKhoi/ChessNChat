//
// Created by entropy on 2/25/19.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATABASE_DIR "database"
#define USER_DIR "database/user/"
#define CHAT_DIR "database/chat/"

/* Returns the userId of the user created */
int createUser(char* username, char* password);

/* Returns 0 for a non-exist user;
 * returns 1 for a successful operation;
 * returns -1 for an unknown invalid operation */
int deleteUser(int userId);

/* Returns 0 for user non-exist; returns 1 for an existing user. */
int checkUserExist(int userId);

/* Returns the next available user id, returns -1 for an unknown invalid operation */
int nextUserId();

/* Returns a list of userIds that ends with an 0
 * Notice that the maximum number of users it can return is 100! */
int* listAllUsers();

/* Returns the user Id when the verification is successful;
 * Returns 0 when the username does not exist;
 * Returns -1 when the password is not correct;
 * Returns -2 when unknown exception happens */
int loginVerification(char* username, char* password);

/* Get the password of the user with userId */
char* getPassword(int userId);

/* Get the username of the user with userId */
char* getUsername(int userId);

/* Print a list of user IDs */
void printUserIdList(int* userIdLst);

/* add the user with friend_userId to the friend list of the userId
 * Returns 0 for duplicated friend Id
 * Returns 1 for successful operation */
int addFriend(int userId, int friend_userId);

/* return the list of friend with type int* of user with userId */
int* getFriendList(int userId);

/* Delete the friend with friend_userId from the friend list of the user with UserId */
int deleteAllFriend(int userId);

/* set the status of a user with userId
 * Status -1 for user does not exist
 * Status 0 for offline
 * Status 1 for online
 * status 2 for busy */
int setStatus(int userId, int status);

/* get the status of a user with userId */
int getStatus(int userId);

/* Get the list of chatId of a user with UserId */
int* getMessageQueue(int userId);

/* append a message to the Message Queue */
int appendMessageQueue(int userId, int fromId, char* message);

/* return the message correspond to a message id */
char* getMessage(int messageId);

/* clear the queue of the message */
int clearQueue(int userId);

char* userId_int2str(int userId);

int userId_str2int(char* userId);

#endif //DATABASE_H
