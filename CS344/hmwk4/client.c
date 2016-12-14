//Travis Robinson
//CS344
//Program 4
//client.c
//Baed off http://www.linuxhowtos.org/C_C++/socket.htm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
void strip_new_lines(char buffer_text[],char buffer_key[]);
void send_string(int sockfd,char buffer[],int text_size);
void receive_string(int sockfd, char buffer[],int text_size);
struct sockaddr_in struct_maker(int port);
void fill_text(char *fileName,char buffer[], int text_size);
int verify_valid_chars(char buffer[],char valid_chars[]);
int verify_input(char buffer_text[], char buffer_key[], char valid_chars[],char *fileName_text,char *fileName_key);
int main(int argc, char *argv[])
{
	int sockfd, port = atoi(argv[3]), n, missing = 0;//sock is socket, port=port connecting on, missing used for tracking received date
        int text_size = 1000000, prog_name_size = 10;//large value selected due to unknown text size;
	struct sockaddr_in serv_addr;//create socket sctruct
	struct hostent *server;//create server struct
	char *fileName_text = argv[1], *fileName_key = argv[2];//text and key file names
        char buffer_cipher[text_size], buffer_text[text_size], buffer_key[text_size], prog_type[prog_name_size], prog_type_connection[prog_name_size];//strings for text, cipher,program name, etc
        char valid_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";//create array of valid chars for comparing

	fill_text(fileName_key,buffer_key,text_size);//use fill text function to read key into key string
	fill_text(fileName_text,buffer_text,text_size);//use fill text function to read text into string

	if (verify_input(buffer_text,buffer_key,valid_chars, fileName_text, fileName_key) == 0)//if verify input function says text and key are bad, exit w/ value 1
	{
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);//create socket, print error if it fails
	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}
	server = gethostbyname("localhost");//server will be local host by assignment requirements
	serv_addr = struct_maker(port);	//use function to create socket using desired port
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //connect to desired port
	{
		error("ERROR connecting");
	}

	uint32_t newPort = 0;//receive new port from server program
	n = recv(sockfd,&newPort,sizeof(newPort),0);
	if (n < 0)
	{
		error("ERROR writing text to socket");
	}
	close(sockfd);//close old socket

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}
	serv_addr = struct_maker(newPort);//create new socket struct using new port	

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		error("ERROR connecting");
	}

	strcpy(prog_type,argv[0]);
	send_string(sockfd, prog_type,prog_name_size);//send name of program to verify connection is allowed
	n = recv(sockfd,prog_type_connection,prog_name_size,0);//receive name of connecting program (rather type, since _d is stripped off)
//	receive_string(sockfd, prog_type_connection, prog_name_size);
	if(strcmp(prog_type,prog_type_connection) != 0)//make sure that connection is allowed with other program, of not exit w/ value 2
	{
		fprintf(stderr,"Error: not allowed to communicate with %s_d on port %d: can only talk to %s_d\n",prog_type_connection,port,prog_type);
		close(sockfd);
		exit(2);
	}
	send_string(sockfd, buffer_text, text_size);//use send string function to send text/sipher (depending on whether this is a decrypt or encrypt program
	receive_string(sockfd, buffer_cipher,18);//recieve a message so that streams arent' jumbled together (using blocking nature of send and receive) 
	send_string(sockfd, buffer_key, text_size);//send key over to other program

	receive_string(sockfd,buffer_cipher,text_size);//receive encrypted/decrypted text into cipher text
	write(1,buffer_cipher,strlen(buffer_cipher));//write cipher/decrypted text to stdout

	close(sockfd);//close socket and end program
	return 0;
}
//this function verifies that legal input is used, if not return 0 else return 1
int verify_input(char buffer_text[], char buffer_key[], char valid_chars[],char *fileName_text, char *fileName_key)
{
	strip_new_lines(buffer_text, buffer_key);//strip new lines for ease of using text
	if(strlen(buffer_text) > strlen(buffer_key))//verify key is long enough
	{
		fprintf(stderr,"Error: key '%s' is too short\n",fileName_key);
		return(0);
	}
	if(verify_valid_chars(buffer_text,valid_chars) == 0)//verify text contains no bad chars
	{
		fprintf(stderr,"otp_enc_d error: input %s contains bad characters\n",fileName_text);
		return(0);
	}
	if(verify_valid_chars(buffer_key,valid_chars) == 0)//verify key contains no bad chars
	{
		fprintf(stderr,"otp_enc_d error: input %s contains bad characters\n",fileName_key);
		return(0);
	}
	return(1);
}
int verify_valid_chars(char buffer[],char valid_chars[])//this function verifies that the called on string contains valid chars, returns 0 if does, 1 if string is acceptable
{
	int i = 0;
	while(i < strlen(buffer))
        {
                int j = 0;//with each char of text, loop through valid chars
                while(j < 27)
                {
                        if(buffer[i] == valid_chars[j])//if the char is the same as one of the valid chars, break loop
                        {
                                break;
                        }
                        if(buffer[i] == '\n')//it's okay for new line to be at end of file
                        {
                                break;
                        }
                        j++;
                        if(j==27)//if the loop is never broken, then a valid char was never found
                        {
                              return(0); 
                        }
                }
                i++;
        }
	return(1);
}
//this text reads into the desired buffer the text from the desired file name
void fill_text(char *fileName,char buffer[], int text_size)
{
	int fd;
	fd = open(fileName,O_RDONLY);//read in text from the named file
        read(fd,buffer,text_size);
        close(fd);
}
//this function creates the socket struct based on desired port
struct sockaddr_in struct_maker(int port)
{
        struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
        return serv_addr;
}
//this function receives a string from the other program, reads it into the desired buffer
void receive_string(int sockfd,char buffer[],int text_size)
{
	int n;
	int missing = 0;//counter used to make sure all text received
	char *full_string;//pointer to a string used to accumulate data until it's all received
	full_string = (char*) malloc(text_size);
        while (missing < text_size)
        {       
		 char *partial_string;//create partial string to hold data currently being received
                partial_string = (char * )malloc(text_size);
                n = recv(sockfd,partial_string,text_size,0);//print an error if something goes wrong, otherwise receive data
                if(n < 0)
                {
                        fprintf(stderr,"error recv text\n");
                        break;
                }
                missing = missing + n;//add amount of received data until we reach the expected amount to receive
                strcat(full_string,partial_string);//add what was just received to accumulated receivals
                free(partial_string);//release partial string
        }
        strcpy(buffer,full_string);//copy received string into desired buffer
        free(full_string);//free string to prevent memory leak
        return;
}
//this function sends the desired string to the desired program via socket
void send_string(int sockfd,char buffer[],int text_size)
{
	int n;
	n = send(sockfd,buffer,text_size,0);//send, check for errors and print to screen
	if (n < 0) 
	{
		error("ERROR writing text to socket");
	}
}
//this function strips new lines at end of file and replaces with terminating character for ease of use
void strip_new_lines(char buffer_text[],char buffer_key[])
{
	int text_size = sizeof(buffer_text);//set text_size to size of input
	int i = 0;
	while(i < text_size)
	{
		if(buffer_text[i] == '\n')//replace new line of text and key with null char
		{
			buffer_text[i] = '\0';
		}
		if(buffer_key[i] == '\n')
		{
			buffer_key[i] = '\0';
		}
		i++;
	}
}

