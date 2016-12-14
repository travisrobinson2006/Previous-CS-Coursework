Travis Robinson
CS372
Project 1
Fall 2016
Oregon State University

Compilation Instructions, Execution and Control Instructions: 

To compile the chatserver, type into the command line "javac chatserver.java" without the quotes.
To compile the chatclient, type into the command line "gcc chatclient.c -o chatclient" also without the quotes.

Using two seperate windows into flip (via Putty or something similar), first run chatserver by entering 
"java chatserver ####" into the command line no quotes without quotes and where #### is the port you wish to run 
on (such as 1234 or 30000). It will then ask you to enter a server handle. After doing that, it will display
a message stating that "Server is ready to receive on port ####".

Next run chatclient by typing "./chatclient chatserver_flip_server ####" into the command line, again without
quotes, where "chatserver_flip_server" is the flip server that chatserver is running on (such as 
flip1.engr.oregonstate.edu which is what I used for the majority of my testing) and #### is the port that you 
told chatserver to run on. Chat client will then ask for a client user handle.

From there, the chatclient will display the handle of the server, and will then ask the user for a message.
Each message can be up to 500 characters long. Afte the message is sent, chatserver will then be asked to 
send a message in response. No message can be sent until a message is received first. Incoming messages will
be denoted by the user name of the other entity (so if you are looking at the client, the user name of the
server will be displayed) followed by a colon (':'). When it is an entities turn to respond, the command line
will have the user handle of the enitity along with a '>' symbol. For example, if client were the user name,
when it is the client turn to send a message, the command line would display 'client>'.

When either user is ready to quit, the exit command is "\quit" without quotes.

Notes:

The original project requirements said to prepend each message with the user name. On the discussion board the
professor said it was okay to have the client and the serve exchange handles in the beginning and display them
themselves, and this is what I did on this project.

I used multiple flip servers, but flip1 was the one used the most.


Sources:

For chatserver: http://docs.oracle.com/javase/tutorial/networking/sockets/index.html
For chatclient: https://beej.us/guide/bgnet/output/html/multipage/index.html