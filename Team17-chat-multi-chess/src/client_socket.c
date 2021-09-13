//
// Created by entropy on 3/1/19.
//
// 
#include "client_socket.h"

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

int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main(int argc, char* argv[])
{
    char command[100] = {0};
    char user_func[25] = {0};
    char username[25] = {0};
    char password[25] = {0};
    char message[256] = {0};
    char input[100] = {0};
    char buffer[256] = {0};
    char sending_command[256] = {0};
    char rec[256] = {0};
    char mes_command[256] = {0};
    char mes_recv[256] = {0};
    int port = -1;

    sscanf(argv[2], "%d", &port);
    if(port<=0){
	printf("Wrong Command Line argument");
	return -1;
    }

BE: printf("Welcome!\nLOGIN or REGISTER?\n>");
    scanf("%s", user_func);
    printf("Enter your username:");
    scanf("%s", username);
    printf("Enter your password:");
//    scanf("%s", password);
   /*hide password*/
	while(1)
	{
    int i = 0;
		int ch = getch();
		if(ch >= 33 && ch <= 126)
		{
			password[i++] = ch;
			printf("* \b");	
		}        

		else if(ch == 8 || ch == 127)
		{
			if(i > 0)
			{
				i--;
				printf("\b \b");		
			}
		}
 /*	
If user put other char outside of 33 to 126, it will break. For example: it will break at enter or tab.
*/  
		else
		{
			password[i] = '\0';
			break;			
		}
	}
    if(strcmp(user_func, "LOGIN") == 0 || strcmp(user_func, "REGISTER") == 0)
    {
        // The user want to login or register
        strcpy(command, user_func);
        strcat(command, ",");
        strcat(command, username);
        strcat(command, ",");
        strcat(command, password);
#ifdef DEBUG
        printf("Sending Message \'%s\' to server ... \n", command);
#endif
    } else
    {
        // Wrong input
        printf("Wrong input\n");
        goto BE;
    }

    strcpy(buffer, get(command, port));

#ifdef DEBUG
    printf("Message Received from server: %s\n", buffer);
#endif

    if(strcmp(buffer, "0") != 0 && strcmp(buffer, "-1") != 0 && buffer != 0)
    {
        printf("Successful!\n Your User ID is:%s\n", buffer);
    }
    else
    {
        printf("EXCEPTION!!\n");
        return 0;
    }

SE: printf("SEND or GET?");
    scanf("%s", input);
    if(strcmp(input, "SEND") == 0)
    {
        // the user want to send
        printf("To whom? (userId):");
        scanf("%s", input);
        printf(">");
        scanf("%s", message);

        strcpy(sending_command, "SEND,");
        strcat(sending_command, buffer);
        strcat(sending_command, ",");
        strcat(sending_command, input);
        strcat(sending_command, ",");
        strcat(sending_command, message);

        strcpy(rec, get(sending_command, port));
#ifdef DEBUG
        printf("Echo from server:%s\n", rec);
#endif
    }
    else if (strcmp(input, "GET") == 0)
    {
        // the user want to receive
        strcpy(sending_command, "QUEUE,");
        strcat(sending_command, buffer);

        strcpy(rec, get(sending_command, port));
#ifdef DEBUG
        printf("Echo from the server:%s\n", rec);
#endif
        printf("Which Message you wanna read?");
        scanf("%s", message);

        strcpy(mes_command, "MESSAGE,");
        strcat(mes_command, message);

        strcpy(mes_recv, get(mes_command, port));

        printf("%s\n", mes_recv);

    } else
    {
        printf("EXCEPTION!\n");
        return 0;
    };
}