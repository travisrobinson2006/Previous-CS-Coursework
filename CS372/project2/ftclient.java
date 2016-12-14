/*
Travis Robinson
CS372
Project 2
Fall 2016
ftclient.java

Sources:
http://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html
http://stackoverflow.com/questions/4350084/byte-to-file-in-java
https://docs.oracle.com/javase/7/docs/api/java/io/BufferedReader.html#read(char[],%20int,%20int)
http://stackoverflow.com/questions/7655127/how-to-convert-a-char-array-back-to-a-string
http://www.asciitable.com/
http://stackoverflow.com/questions/1816673/how-do-i-check-if-a-file-exists-in-java
 */

import java.util.Scanner;
import java.net.*;
import java.io.*;
import java.lang.*;

public class ftclient {



    public static void main(String[] args) {
        final int MAX_FILE_SIZE = 1080000000;//accept up to a GB file (in theory, only tested to about 150MB, which takes quite a while)
        final int PACKET_SIZE = 1000;//packet size used because I know it'll reach destination
        final int COMMAND_LOCATION = 2;//where the command will be in the command line args
        String hostName= "", command = "", fileName = "";//host name is flip1.engr.oregonstate.edu, etc, command= command to send to server
        String messageString, dataString;//used for displaying/processing data from ftserver
        int commandPortNumber = 0, dataPortNumber = 0;
        final char eof = (char)7;//used to flag when file should be ended
        boolean directory_listing_flag = false, receive_file_flag = false, other_flag = false;//flags used for signaling commands

        //the sockets
        ServerSocket dataSocket;
        Socket socket;

        if (args.length < 4){//not enough args
            System.out.println("Please include an address to connect to, a command port, a command, and a data port");
            System.exit(1);
        }
        else if(args.length > 5){//too many args
            System.out.println("Too many commands. Should only include an address, command port, command, <filename>, and data port");
        }
        else {
            hostName = args[0];
            try{//get command port of server, verify it's a number
                commandPortNumber = Integer.parseInt(args[1]);
            }
            catch (Exception e)
            {
                System.out.println("Error: please enter a valid port number: " + e.toString());
            }

            if (args[COMMAND_LOCATION].equals("-l")) {//user wants listing
                command = command + args[COMMAND_LOCATION] + " ";//add the -l
                directory_listing_flag = true;
                try {
                    dataPortNumber = Integer.parseInt(args[COMMAND_LOCATION + 1]);//get desired dataport, make sure it's a number
                    command = command + args[COMMAND_LOCATION + 1];
                } catch (Exception NumberFormatException) {
                    System.out.println("Data Port Number must be a valid number");
                    System.exit(1);
                }
            }
            else if (args[COMMAND_LOCATION].equals("-g")) {//user wants a file
                command = command + args[COMMAND_LOCATION] + " ";//add the -g
                command = command + args[COMMAND_LOCATION + 1] + " ";//add the file name command
                receive_file_flag = true;
                fileName = args[COMMAND_LOCATION + 1];
                try {
                    dataPortNumber = Integer.parseInt(args[COMMAND_LOCATION + 2]);//get dataport, ensure it's a valid number
                    command = command + args[COMMAND_LOCATION + 2];
                } catch (Exception NumberFormatException) {
                    System.out.println("Data Port Number must be a valid number");
                    System.exit(1);
                }
            }
            else{//user gave incorrect command-validated in client as per professors comment in week 9 Q&A, where validating in client is more efficient so it's better to do
                System.out.println("Unrecognized command. Please use -l <port number> or -g <filename> <portnumber>");
                System.exit(1);
            }
        }

        try {
            //establish control socket
            socket = new Socket(hostName, commandPortNumber);
            //establish data socket
            dataSocket = new ServerSocket(dataPortNumber);//establish dataprot, done here to make sure it's available
            //build reader and writer for control socket
            PrintWriter controlOut = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader controlIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            controlOut.println(command);//send reconstructed command string to ftserver

            //build reader and writer for data socket
            Socket ftserverSocket = dataSocket.accept();
            PrintWriter dataOut = new PrintWriter(ftserverSocket.getOutputStream(), true);
            BufferedReader dataIn = new BufferedReader(new InputStreamReader(ftserverSocket.getInputStream()));

            if(directory_listing_flag == true){//retrieve directory
                char[] size = new char[PACKET_SIZE];
                dataIn.read(size,0,PACKET_SIZE);
                final int file_size = Integer.parseInt(new String(size).trim());//retrieve file size from server, no what size file will be
                dataOut.println("ack");//sent to break block on ftserver, prevent streams from server from running into eachother on clients receiving socket
                System.out.println("Receiving directory from " + hostName + ":" + dataPortNumber);
                dataString = dataIn.readLine().replaceAll(" ", "\n");//replace spaces with new lines for readability of directory contents
                dataString = dataString.substring(0,dataString.indexOf(eof));//remove eof character (and all whitespace etc after it)
                System.out.print(dataString);//put each file on its own line
            }
            else if (receive_file_flag == true){//retrieve desired file
                dataString = "";//where the data will end up going
                int running_total = 0;//running total to know when entire file has been received
                char[] size = new char[PACKET_SIZE];//temp char array, used to get size of file
                dataIn.read(size,0,PACKET_SIZE);//read PACKET_SIZE of bytes
                final int file_size = Integer.parseInt(new String(size).trim());//retrieve size from temp size array above
//                System.out.println("File size: " + file_size);//used for testing
                dataOut.println("ack");//sent to break block on ftserver, prevent streams from server from running into eachother on clients receiving socket
                System.out.println("Receiving \"" + fileName + "\" from " + hostName + ":" + dataPortNumber);
                while (running_total <= file_size){//keep reading and sending ack until entire file received
                    char[] data= new char[PACKET_SIZE];//temp array to read packet contents into
                    dataIn.read(data,0,PACKET_SIZE);//read packet contents into
                    dataOut.println("ack");//ack to prevent bleed over from upcoming packets
                    String tempDataString = new String(data);//convert temp data array into string
                    dataString = dataString + tempDataString;//concat temp string onto data string
                    running_total = running_total + PACKET_SIZE;//update running total
//                    System.out.println(running_total);//used for testing
                }
                dataString= dataString.substring(0,dataString.indexOf(eof));//remove end of file and whitespace, etc after it
                if (!dataString.isEmpty()){//make sure it's not empty before creating file
                    File temp = new File(fileName);
                    FileOutputStream fos;
                    if (temp.exists() && !temp.isDirectory()){
                        int i = 1;
                        while((temp = new File(fileName + "_" + i)).exists() && !temp.isDirectory()){
                            i++;
                        }
                        System.out.println("File already exists. Sending received contents to " + fileName + "_" + i);
                        fos = new FileOutputStream(fileName + "_" + i);//contingency if file already exists
                    }
                    else{
                        fos = new FileOutputStream(fileName);//write to file if there is data to be written
                    }
                    fos.write(dataString.getBytes());
                    fos.close();
                    System.out.println("File transfer complete");//announce transfer complete
                }
            }
            dataSocket.close();//close data socket after transfer complete (done in both server and client for redundancy)
            messageString = controlIn.readLine();//receive any messages from ftserver
            if(messageString != null && !messageString.isEmpty()){//if message is not empty or null, print it, else do nothing
                System.out.println(socket.getRemoteSocketAddress().toString() + ":" + "says ");
                System.out.println(messageString);
            }
            socket.close();//close control socket (done in both server and client for redundancy
        } catch (Exception e){//print any errors (such as dataport for binding being unavailable
            System.out.println(e.toString());
        }
    }
}