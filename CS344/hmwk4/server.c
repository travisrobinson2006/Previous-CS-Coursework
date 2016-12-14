//Travis Robinson
//CS344
//Program 4
//server.c
//Adated from http://www.linuxhowtos.org/C_C++/socket.htm
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdint.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
//This function creates the structs used in socket formation--used to reduce code clutter
struct sockaddr_in struct_maker(int port)
{
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	return serv_addr;
}
void check_kids(pid_t spawnpid, int status);
void encrypt (char buffer_text[],char buffer_key[], char buffer_cipher[],int text_size);
void decrypt (char buffer_text[],char buffer_key[], char buffer_cipher[],int text_size);
void receive_string(int sockfd, char buffer[],int text_size);
int main(int argc, char *argv[])
{
	int status,sockfd,client_sockfd,port,n,s,b,l;//status used for checking on forks, sockfd's used for sockets, port = port to use, n, s, b, l used for error checking sockets and byte streams
	int text_size = 1000000, prog_name_size = 10;//text_size = large value due to unknown size of data received, prog_name_size used when checking on if programs can talk to each other 
	char buffer_text[text_size], buffer_key[text_size], buffer_cipher[text_size], prog_type[prog_name_size], prog_type_connection[prog_name_size];//strings for key, text, name of program, etc
	struct sockaddr_in serv_addr;//socket struct
	pid_t spawnpid = -5;//spawn pid used to check on forks
	strcpy(prog_type,argv[0]);//copy name into prog_type to ensure connection is valid
	prog_type[7] = '\0';//remove _d from prog name to ensure connection is valid
	prog_type[8] = '\0';
	port = atoi(argv[1]);//save port from command line input
	serv_addr = struct_maker(port);//create socket struct using function

	s = (sockfd = socket(AF_INET, SOCK_STREAM, 0));//s = socket
	b = bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)); //b = bind
	l = listen(sockfd,5);//l = listen
	if(s < 0 || b < 0 || l < 0)//check if there's an error in forming connection, exit on error w/ network error
	{
		perror("network error\n");
		exit(1);
	}
	while (1)//while 1 so program continues to run until terminated
	{
		client_sockfd = accept(sockfd,NULL,NULL);//accept calls at top of loop so parent process will continue to accept calls
		if (client_sockfd < 0)
		{ 
			error("ERROR on accept");
		}
		spawnpid = fork();//create fork for concurrency
		if (spawnpid == -1)//terminate fork if an error in forming it 
		{
			perror("forking error");
			exit(1);
		}
		else if (spawnpid == 0)//if fork, then do encryption etc
		{
			srand(time(NULL));//seed random number to generate new port so that main port is still available for next connection

			int sockfd_fork;
			uint32_t newPort = rand() % 1000000;//generate new port number
			struct sockaddr_in serv_addr_fork;
			serv_addr_fork = struct_maker(newPort);//create socket struct using new port and make socket function

			int s = -1, b = -1, l = -1;//initialize values so that while loop is entered 
			while(s < 0 || b < 0 || l < 0 || newPort == port)//enter loop if bad values, generate new port as many times as needed until a valid port number is generated 
			{
				newPort = rand() % 1000000;//generate random number for port
				serv_addr_fork = struct_maker(newPort);//create the new port
				s = (sockfd_fork = socket(AF_INET, SOCK_STREAM, 0));//ensure new port is valid; if it's not while loop will continue until a valid port is found
				b = bind(sockfd_fork, (struct sockaddr *) &serv_addr_fork,sizeof(serv_addr_fork)); 
				l = listen(sockfd_fork,5);
			}
			n = send(client_sockfd,&newPort,sizeof(newPort),0);//send new port number
			close(client_sockfd);//close old port
			client_sockfd = accept(sockfd_fork,NULL,NULL);
			n = recv(client_sockfd,prog_type_connection,prog_name_size,0);//receive name of connecting program
			n = send(client_sockfd,prog_type,prog_name_size,0);//send name of program, other program will print error if needed
			if (strcmp(prog_type,prog_type_connection) != 0)//exit fork with error code 2 if connecting function is not valid
			{
				close(client_sockfd);
				exit(2);
			}
			if (client_sockfd < 0)
			{ 
				error("ERROR on accept");
			}
			receive_string(client_sockfd,buffer_text,text_size);//receive text from connecting function using recevie_string function
			n = send(client_sockfd,"I got your message",18,0);//send message to prevent next message from being mixed in with the previous
//			n = write(client_sockfd,"I got your message",18);
			receive_string(client_sockfd,buffer_key,text_size);//receive key using receive key function
			if(strcmp(prog_type,"otp_enc") == 0)//if statement to determine if program is supposed to encrypt or decrypt based on what the program is called
			{
				encrypt (buffer_text,buffer_key,buffer_cipher,text_size);//call on encrypt function if that is purpose of program
			}
			else if(strcmp(prog_type,"otp_dec") == 0)
			{
				decrypt (buffer_text,buffer_key,buffer_cipher,text_size);//call on decrpypt if that is purpose of function
			}
			else
			{
				fprintf(stderr,"unkown program\n");//if program has unknown name, it's purpose is unknown so print message
				exit(5);//exit with code if unknown program purpose
			}
			n = send(client_sockfd,buffer_cipher,text_size,0);//encrypt/decrypt will alter cipher text, send cipher back to calling function
									// (cipher in this case may also be decrypted cipher
			if (n < 0)
			{
				error("ERROR writing to socket");
			}
			close(client_sockfd);//close sockets, end fork with success code
			close(sockfd);
			return 0; 
		}
		check_kids(spawnpid,status);//if not a fork then it's the parent and needs to check on kids
	}
}
//this function receives messages from connecting function, inputs them into desired string
void receive_string(int sockfd,char buffer[],int text_size)
{
	int n;//for error checking
	int missing = 0;//to make sure entire string is received, total number of bytes received
	char *full_string;//pointer to the full string
	full_string = (char*) malloc(text_size);//allocate space for the full string
	while (missing < text_size)//continue through loop until entire message is received
	{
		char *partial_string;//create and allocate space for a partial string to recieve byte stream
		partial_string = (char * )malloc(text_size);
		n = recv(sockfd,partial_string,text_size,0);//recevie byte stream, check for errors
		if(n < 0)
		{
			printf("error recv text\n");
			break;
		}
		missing = missing + n;//add number of bytes received to total number of bytes
		strcat(full_string,partial_string);//concatenate what was just received to compilation of what has been received
		free(partial_string);//free space for the partial string
	}
	strcpy(buffer,full_string);//once full data received, copy it into desired string
	free(full_string);
	return;
}
//this function encrypts text using key, puts it in cipher
void encrypt (char buffer_text[],char buffer_key[], char buffer_cipher[],int text_size)
{
	int i;//a counter
	strncpy(buffer_cipher,buffer_text,text_size);//copy original text into cipher
	i = 0;
	while (i < strlen(buffer_cipher))//go through entire length of text to encrypt it
	{
		if(buffer_cipher[i] != '\0' && buffer_cipher[i] != '\n')//don't do anything if a newline (contained at end of text) or null char 
		{
			if(buffer_cipher[i] == ' ')//replace space w/ bracket for ease of encryption 
			{
				buffer_cipher[i] = '[';
			}
			if(buffer_key[i] == ' ')
			{
				buffer_key[i] = '[';
			}
			buffer_key[i]= buffer_key[i] - 64;//subtract 64 so that least value will be 1 on ascii table, thus incrementing each letter the appropriate number of values 
			buffer_cipher[i] = buffer_cipher[i] + buffer_key[i];//increment the cipher
			if (buffer_cipher[i] > 91)//if the new char value is too high on ascii table, take it back into desired ascii values (the capital alphabet)
			{
				buffer_cipher[i] = buffer_cipher[i] - 27;
			}
			if (buffer_cipher[i] == '[')//return brackets with spaces
			{
				buffer_cipher[i] = ' ';
			}
		}
		i++;
	}
	return;
}
//this function decrypts, placing decrpted text into cipher--text will be encrypted text
void decrypt (char buffer_text[],char buffer_key[], char buffer_cipher[],int text_size)
{
	int i;
	strncpy(buffer_cipher,buffer_text,text_size);//copy encrypted text into cipher
	i = 0;
	while (i < strlen(buffer_cipher))//go through each value of the text
	{
		if(buffer_cipher[i] != '\0' && buffer_cipher[i] != '\n')//don't do anything if at end of the text
		{
			if(buffer_cipher[i] == ' ')//replace space with bracket for ease of decryption
			{
				buffer_cipher[i] = '[';
			}
			if(buffer_key[i] == ' ')
			{
				buffer_key[i] = '[';
			}

			buffer_key[i] = buffer_key[i] - 64;//subtract 64 so base value will be 1 (since starting values are at 65 on ascii)  
			buffer_cipher[i] = buffer_cipher[i] - buffer_key[i];
			if (buffer_cipher[i] < 65)//if char is less than accepted values, add to it to bring it back into the correct subset of ascii table
			{
				buffer_cipher[i] = buffer_cipher[i] + 27;
			}


			if (buffer_cipher[i] == '[')//return spaces to where brackets are
			{
				buffer_cipher[i] = ' ';
			}
		}
		i++;
	}
	return;

}
//this function is used by the parent to check on the status of its children and make sure they've completed their task
void check_kids(pid_t spawnpid, int status)
{
	spawnpid = waitpid(-1,&status,WNOHANG);
	while (spawnpid != 0)
	{
		spawnpid = waitpid(-1,&status,WNOHANG);
	}
}

