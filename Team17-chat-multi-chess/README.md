# Team17

## How to connect to the server?
1. Include the "socketTester.h" in your source code
```#include "socketTester.h""```
2. Call function ```char* get(char* command, int port)``` each time calling the protocol.
3. Handles the result in your own code and the detailed information about the protocol is shown below.

## Detailed description about the protocols
#### Login
* Usage: ```LOGIN,[Username],[Password]```
* Example: ```LOGIN,Entropy,123456```
* Returned Value:
    1. Returns 0 if the user does not exist.
    2. Returns -1 if the password is incorrect.
    3. Returns -2 for unknown **EXCEPTION**.
    4. Returns a postive integer which corresponds to the user ID of the logined user if the login is successful.

#### Register
* Usage: ```REGISTER,[Username],[Password]```
* Example: ```REGISTER,Entropy,123456```
* Returned Value:
    1. Returns value <= 0 for **EXCEPTION**
    2. Returns a postive integer which is the user Id of the user registered for a successful registration.

#### Get Username
* Usage: ```GETNAME,[UserID]```
* Example: ```GETNAME,01```
* Returned Value:
    1. Returns **EMPTY** for user does not exist
    2. Returns the username of the user if the user exists.

#### Get Message Queue
* Usage: ```QUEUE,[UserID]```
* Example: ```QUEUE,01```
* Note: You are supposed to make sure the userId exists before calling this protocol.
* Returned Value:
    1. Returns **EMPTY** for No incoming message.
    2. Returns a list of integer seperated by "," for a successful operation. The list of integer corresponds to the
    message queue.
* Example Returned Value: ```00000001,00000003,00000005```

#### Get Message from MessageID
* Usage ```MESSAGE,[MessageID]```
* Example: ```MESSAGE,041```
* Returned Value:
    1. Returns **EMPTY** for message not exist.
    2. Returns a integer which is where the message came from and the content of the message seperated by a ","".

#### Send Message 
* Usage: ```SEND,[FromUserId],[ToUserId],[MessageContent]```
* Example: ```SEND,01,02,HelloWorld!```
* Returned Value:
    1. Returns 1 for successful operation
    
#### Get Friends List
* Usage: ```GETFRI,[UserID]```
* Example: ```GETFRI,01```
* Returned Value:
    1. Returns **EMPTY** for no friends in the friend list.
    2. Returns a list of integers seperated by "," for the friend list. Each integer in the list corresponds to the 
    user id of the friend.

#### Add Friend
* Usage ```ADDFRI,[UserID],[FriendID]```
* Example: ```ADDFRI,01,02```
* Returned Value:
    1. Returns 1 for a successful operation.

#### Delete Friend
* Usage ```DELETEFRI,[UserID],[FriendID]```
* Example: ```DELETEFRI,01,02```
* Returned Value:
    1. Returns 1 for a successful operation.

#### Get Status of User
* Usage: ```GETSTAT,[UserID]```
* Example: ```GETSTAT,01```
* Returned Value:
    1. Returns 0 if the user is offline.
    2. Returns 1 if the user is online.
    3. Returns 2 if the user is busy.
    4. returns 3 if the user does not exist.

#### Set the Status of User
* Usage: ```SETSTAT,[UserID],[Status]```
* For Status: 0 for offline; 1 for online; 2 for busy.
* Example: ```SETSTAT,01,01```
* Returned Value:
    1. Return 1 for a successful operation.
