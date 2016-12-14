/*
Travis Robinson
Project 1
CS 372
Source: https://beej.us/guide/bgnet/output/html/multipage/index.html
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define MAX_TXT_SIZE 600
#define MAX_HANDLER_SIZE 20

void *get_in_addr(struct sockaddr *sa);
int receiveMessage(int sockfd, char buffer[], char serverHandle[]);
int sendMessage(int sockfd, char buffer[], char userHandle[]);

main(int argc, char **argv)
{
    //establish variables
    char userHandle[MAX_HANDLER_SIZE], serverHandle[MAX_HANDLER_SIZE], buffer[MAX_TXT_SIZE], s[INET6_ADDRSTRLEN], *ip, *port, *ptr;
    int status, sockfd;
    struct addrinfo hints, *servinfo, *res;

    //ensure user provides a handle and server address,port
    if (argc < 3)
    {
        printf("You must include a server IP and Port");
        return;
    }
    else
    {
        ip = argv[1];
        port = argv[2];
        printf("Connecting to %s on port %s\n",ip,port);
    }

    //get user handle
    printf("Input Handle: ");
    ptr = userHandle;
    fgets(ptr,MAX_HANDLER_SIZE,stdin);

    //prepare socket struct
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    //verify getaddrinfo
    status = getaddrinfo(ip,port,&hints,&servinfo);
    if ( status != 0)
    {
        printf("%s",gai_strerror(status));
    }

    //find valid connection
    for ( res = servinfo; res != NULL; res = res->ai_next)
    {
        if ((sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) == -1)
        {
            perror("client:socket");
            continue;
        }

        if (connect(sockfd,res->ai_addr,res->ai_addrlen) == -1){
            close(sockfd);
            perror("client:connect");
            continue;
        }
        break;
    }
    //display this if there was an error in finding connections
    if (res==NULL)
    {
        printf("client:failed to connect\n");
        return;
    }

    //establish connection
    inet_ntop(res->ai_family, get_in_addr((struct sockaddr *)res->ai_addr),s, sizeof s);

    //send user handle
    send(sockfd,userHandle,MAX_HANDLER_SIZE,0);

    int i = 0;
    while (i < MAX_HANDLER_SIZE){
        if (userHandle[i] == '\n'){
            userHandle[i] = '>';
        }
        i++;
    }

    //receive servers user handle
    ptr = serverHandle;
    printf("Connected To: ");
    recv(sockfd,ptr,MAX_HANDLER_SIZE,0);

    i = 0;
    while (i < MAX_HANDLER_SIZE){
        if (serverHandle[i] == '\n'){
            serverHandle[i] = '\0';
        }
        i++;
    }

    printf("%s\n",serverHandle);
    memset(buffer,0,MAX_TXT_SIZE);//clear buffer to remove leftovers of previous message

    while(1)
    {
        //send message to server, exit if return val of 1
        if (sendMessage(sockfd,buffer,userHandle)==1)
        {
            printf("Connection to %s terminated\n",serverHandle);
            break;
        }
        //receive message from server, exit if return val of 1
        if (receiveMessage(sockfd,buffer,serverHandle) == 1)
        {
            printf("%s left the chat\n",serverHandle);
            break;
        }
    }

    //free memory no longer needed
    freeaddrinfo(servinfo);
    close(sockfd);
}

/*
The function takes in user input and sends the outgoing message to the server. It also checks to see
if the outgoing message is the termination signal and will return 1 if the program needs to terminate
*/
int sendMessage(int sockfd, char buffer[], char userHandle[])
{
    char * ptr = buffer;//get user input
    printf("%s",userHandle);
    fgets(ptr,MAX_TXT_SIZE,stdin);

    if (strcmp(buffer,"\\quit\n") == 0){//send message and quit if quit command
        send(sockfd,buffer,MAX_TXT_SIZE,0);
        return 1;//flag that it's quittin' time
    }
    else{
        send(sockfd,buffer,MAX_TXT_SIZE,0);//send message if no quit command
    }
    memset(buffer,'\0',MAX_TXT_SIZE);//clean up buffer after use
}
/*
This function receives the message from the server and prints it. It also checks to see if it is
a termination signal and returns 1 if the program needs to shut down.
*/
int receiveMessage(int sockfd, char buffer[], char serverHandle[])
{
    char * ptr = buffer;
    recv(sockfd,ptr,MAX_TXT_SIZE,0);
    if (strcmp(buffer,"\\quit\n") == 0){
        return 1;
    }
    printf("%s:",serverHandle);
    printf(buffer);
    memset(buffer,'\0',MAX_TXT_SIZE);
}

/*
This function sets up the socket to be IP4 or IP6
*/
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
