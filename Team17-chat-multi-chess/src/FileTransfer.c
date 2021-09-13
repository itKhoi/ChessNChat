#include "FileTransfer.h"

/* 
This function will read the file and send it throught the socket. It will handle all the file types.
*/
int receive_file(int socket)
{
	FILE *file;
	/* user will type the file name that he wants to save with */
	char file_name[40];
	
	do
	{
		size_bytes = read(socket, &size, sizeof(int));
	}while(size_bytes < 0);
	
	/* create an array to store the file that is going to receive.*/
	char* FileArray = malloc(size);

	printf("Package received.\n");
	
	do
	{
		size_bytes = write(socket, "received the package", sizeof(int));
	}while(size_bytes < 0);
	
	printf("Package successfully received signal sent\n\n");

	while(1){
		printf("Please enter the name to save the file including file type (max 40 char): ");
		scanf("%19s", file_name);
		file = fopen(file_name, "w");
   		if(!file)
		{
			printf("Error: file could not be opened\n");
		}
		else
		{
			break;		
		}
	}

	while(receive_size < size){

		do
		{
			read_size = read(socket, FileArray, size);
		}while(read_size <0);

		write_size = fwrite(FileArray, 1, read_size, file);
		receive_size = receive_size + read_size;
		package_number++;
	}

	fclose(file);
	free(FileArray);
	printf("File Received and written successfully!\n");
	return 0;
}

/* 
This function will receive the file and send it throught the socket. It will handle all the file types.
*/
int send_file(int socket)
{
	FILE *file;
	char file_name[40];
	
	while(1)
	{
		printf("Please enter the file name to send including file type (max 40 char): ");
		scanf("%19s", file_name);	
		file = fopen(file_name, "r");
   		if( !file )
 		{
			printf("Error: file could not be opened.\n");
		}
		else
		{
			break;		
		}
	}
	/* Getting the size of the file. fseek() is moving the pointer. SEEK_END means end of the file */
	fseek(file, 0, SEEK_END);

	/* ftell() return the size of the file. It returns the current value of the position indicator */
	size = ftell(file);

	/*fseek() is moving the pointer. SEEK_SET means beginning of the file */
	fseek(file, 0, SEEK_SET);

	char* FileArray = malloc(size);
	char* read_buffer = malloc(size);
	
	write(socket, &size, sizeof(int));

	do 
	{
		size_bytes=read(socket, read_buffer , size);
	} while (size_bytes < 0);
	
/* feof(file) function returns a non-zero value when End-of-File indicator associated with the stream is set, else zero is returned.*/
	while(!feof(file)) 
	{
		read_size = fread(FileArray, 1, size, file);
		
		do
		{
			size_bytes = write(socket, FileArray, read_size);  
		}while (size_bytes < 0);
		package_number++; 		
		bzero(FileArray, sizeof(FileArray));
	}

/* Close the file and free the meory space for malloc()*/
	fclose(file);
	free(read_buffer);
	free(FileArray);
	printf("File Sent successfully!\n");
	return 0;
}

