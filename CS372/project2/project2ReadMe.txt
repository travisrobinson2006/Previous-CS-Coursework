Travis Robinson
CS372
Project 2
Fall 2016
Oregon State University
ReadMe

Instructions:
To compile ftserver, log on to the flip server of your choice, and enter at the 
command line gcc ftserver.c -o ftserver. To run it enter at the command line
./ftserver ####, where #### is the port of your choice. ftserver is now listening
on that port for a connection from ftclient.

To compile ftclient, log on to the flip server of your choice and enter at the
command line javac ftclient.java. To run it enter at the command line
java ftclient xxxx ####_1 command ####_2, where xxxx is the address that ftserver
is running on (such as flip1.engr.oregonstate.edu), ####_1 is the port number that
ftserver is listening on, command is the command of your choice, and ####_2 is port
number that you would like ftserver and ftclient to run on. There are two options for 
commands: -l, which returns to ftclient a list directory listing of where ftserver is,
and -g fileName, which commands ftserver to send fileName to ftclient (both -g and 
fileName are required). fileName can be any text file, such as test.txt. Any other 
commands will have an error message generate by ftclient. If you attempt to request 
a nonexistant file from ftserver, ftserver will send an error message to ftclient 
using the command port specified at ftserver start.

Souces:
For ftclient:
http://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html
http://stackoverflow.com/questions/4350084/byte-to-file-in-java
https://docs.oracle.com/javase/7/docs/api/java/io/BufferedReader.html#read(char[],%20int,%20int)
http://stackoverflow.com/questions/7655127/how-to-convert-a-char-array-back-to-a-string
http://www.asciitable.com/
http://stackoverflow.com/questions/1816673/how-do-i-check-if-a-file-exists-in-java

For ftserver:
http://beej.us/guide/bgnet/output/html/multipage/syscalls.html
http://beej.us/guide/bgnet/output/html/multipage/getpeernameman.html
http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
http://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
http://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html