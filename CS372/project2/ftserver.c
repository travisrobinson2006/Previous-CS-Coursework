/*
Travis Robinson
CS372
Project 2
Fall 2016
ftserver.c

Sources:
http://beej.us/guide/bgnet/output/html/multipage/syscalls.html
http://beej.us/guide/bgnet/output/html/multipage/getpeernameman.html
http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
http://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
http://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define BACKLOG 10
#define INET6_ADDSTRLEN 46
#define COMMAND_SIZE 100//arbitrary size limit of commands
#define RESPONSE_SIZE 1080000000//be able to send files up to a GB in size
#define PACKET_SIZE 1000//packet size that we know will make it to dest (can prolly go bigger though)

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

main(int argc, char **argv)
{
    //control varaiables
    char command[COMMAND_SIZE], ipstr[INET6_ADDSTRLEN];//command and ip address from client
    char * port, * tok, * response;//control prot, tok for tokenizing command, the response sent to client
    int status;
    int sockfd, new_sockfd;
    int send_directory_flag = 0, send_file_flag = 0, bad_command_flag = 0;//flags to determine what should be sent to client
    int i = 0;//a counter
    char dataport[64], fileName[FILENAME_MAX];//used to send data back to client
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    //malloc response--need to malloc instead of make [] because of large file sizes--must malloc to have sufficient memory
    response = (char *) malloc(RESPONSE_SIZE * sizeof response);

    //data connection variable
    struct addrinfo dataHints, *dataServinfo, *dataRes;
    int dataSock;

    if (argc < 2)//insufficient args
    {
        printf("You must include a Port number/n");
        return;
    }
    else
    {
        port = argv[1];
        printf("Server open on port %s\n",port);//not really but will be soon...
    }
    //make socket to receive commands from clients
    if ((status = getaddrinfo(NULL, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    //make the socket and bind it
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if ((status = bind(sockfd, res->ai_addr, res->ai_addrlen)) == -1){
        fprintf(stderr, "binding error, try another port\n");
        exit(1);
    }
    //start listening, keep backlog of 10
    if ((status = listen(sockfd, BACKLOG)) == -1){
        fprintf(stderr, "listening error\n");
        exit(1);
    }

    addr_size = sizeof their_addr;



    while(1){//remain in while loop to keep accepting new connections
        memset(command,'\0',COMMAND_SIZE);//clear command
        memset(response,'\0',RESPONSE_SIZE);//clear response
        //accept new connections
        new_sockfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);//accept next in queue

        //get their ip address to display to user
        if (their_addr.ss_family == AF_INET) {
            struct sockaddr_in *s = (struct sockaddr_in *)&their_addr;
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        } else { // AF_INET6
            struct sockaddr_in6 *s = (struct sockaddr_in6 *)&their_addr;
            inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
        }

        //print who we're connected with
        printf("Connection from: %s\n", ipstr);

        //receive and parse commands from client
        recv(new_sockfd,command,COMMAND_SIZE,0);
        tok = strtok(command, " \n");
        if (tok != NULL){
            if (strcmp(tok,"-l") == 0){
                tok = strtok(NULL," \n");
                strcpy(dataport,tok);
                send_directory_flag = 1;
            }
            else if (strcmp(tok,"-g") == 0){
                tok = strtok(NULL," \n");
                strcpy(fileName,tok);
                tok = strtok(NULL," \n");
                strcpy(dataport,tok);
                send_file_flag = 1;
            }
            else
            {
                bad_command_flag = 1;
            }
        }
        memset(command,'\0',COMMAND_SIZE);//clear command


        //prepare data socket struct
        memset(&hints,0,sizeof hints);
        dataHints.ai_family = AF_UNSPEC;
        dataHints.ai_socktype = SOCK_STREAM;

        //verify getaddrinfo for data socket
        status = getaddrinfo(ipstr,dataport,&dataHints,&dataServinfo);
        if ( status != 0)
        {
            printf("%s",gai_strerror(status));
        }

        //find valid connection
        for ( dataRes = dataServinfo; dataRes != NULL; dataRes = dataRes->ai_next)
        {
            if ((dataSock = socket(dataRes->ai_family,dataRes->ai_socktype,dataRes->ai_protocol)) == -1)
            {
                perror("client:socket");
                continue;
            }

            if (connect(dataSock,dataRes->ai_addr,dataRes->ai_addrlen) == -1){//connect to datasocket
                close(dataSock);
                perror("client:connect");
                continue;
            }
            break;
        }
        //display this if there was an error in finding connections
        if (dataRes==NULL)
        {
            printf("client:failed to connect\n");
            return;
        }

        //establish connection with datasocket on ftclient
        inet_ntop(dataRes->ai_family, get_in_addr((struct sockaddr *)dataRes->ai_addr),ipstr, sizeof ipstr);
        //client asked for the directory
        if (send_directory_flag == 1){
            printf("List directory requested on port %s\n",dataport);
            fflush(stdout);//flush to ensure prints
            DIR *dp = opendir("./");
            struct dirent *ep;
            if (dp != NULL){
                while (ep = readdir(dp)){
                    if (strcmp(ep->d_name,".") != 0 && strcmp(ep->d_name,"..") != 0){//remove . and .. from list of files (won't remove other directories)
                        strcat(response,ep->d_name);
                        strcat(response," ");
                    }
                }
            }
            else{
                perror("couldn't open directory\n");
            }
            (void) closedir(dp);
        }

        //user asked for a file
        else if (send_file_flag == 1)
        {
            //data used for sending file
            printf("File \"%s\" requested on %s\n",fileName,dataport);
            fflush(stdout);
            FILE *fileptr;
            long filelen;

            fileptr = fopen(fileName, "rb");//open the file in binary mode
            if (fileptr != NULL)
            {
                fseek(fileptr, 0, SEEK_END);//get size of file
                filelen = ftell(fileptr);
                rewind(fileptr);

                fread(response, filelen, 1, fileptr);//read file
                fclose(fileptr);
            }
            else//fileptr is null, file was not found
            {
                memset(response,'\0',RESPONSE_SIZE);//will want to send empty response
                memset(command,'\0',COMMAND_SIZE);//make sure previously used command string is empty
                printf("File not found. Sending error message to %s:%s\n",ipstr,port);
                strcpy(command,"FILE NOT FOUND");//send file not found error message to ftclient
            }
        }

        char eof[] = {(char)7};//eof character used to mark where end of file is for client to remove excess
        strcat(response,eof);//used to signal to ftclient that end of stream is nigh
        strcat(response,"\n");//used to signal to ftclient that end of stream is here

        char size[1000];//to send size of file to ftclient
        char ack[1000];//receive ack to block sending next packet--give ftclient a chance to work with packet before sending next one (in other words, client says it's ready for enxt client)
        sprintf(size,"%d",strlen(response));//get size of response (file or directory) and send it to client to know what's expected
//        printf("size: %d\n",strlen(response));//used for testing purposes
        send(dataSock,size,strlen(size),0);//send response size
        recv(dataSock,ack,PACKET_SIZE,0);//receive acknowledgement
//        printf("ack says: %s\n",ack);
        if (strlen(response) < PACKET_SIZE){//only send up to size of packet if packet smaller than base packet size
            send(dataSock,response,strlen(response),0);
        }
        else
        {
            int running_total = 0;//keep running total to know what is sent
            while (running_total <= strlen(response))
            {
                char * packet = (char *) malloc(PACKET_SIZE * sizeof packet);//create packet
                memcpy(packet,&response[running_total],PACKET_SIZE * sizeof packet);//fill packet with appropriate section of file
                running_total = running_total + send(dataSock,packet,PACKET_SIZE,0);//update running total and send packet
                recv(dataSock,ack,PACKET_SIZE,0);//recieve ack that client is ready for next packet
//                printf("%d\n",running_total);
                free(packet);//free packet
            }

        }
        close(dataSock);//close data when it's all sent
        send(new_sockfd,command,strlen(command),0);
        close(new_sockfd);//close socket for data
        send_directory_flag = 0;
        send_file_flag = 0;
        bad_command_flag = 0;
        memset(response,'\0',RESPONSE_SIZE);//clear response
        memset(command,'\0',COMMAND_SIZE);
    }
    close(sockfd);
    freeaddrinfo(res); // free the linked-list
    free (response);//free response
}
