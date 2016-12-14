/*
Travis Robinson
Project 1
CS 372
Source: http://docs.oracle.com/javase/tutorial/networking/sockets/index.html
 */

import java.util.Scanner;
import java.net.*;
import java.io.*;
import java.lang.*;

public class chatserver{

    public static final int maxUserHandleSize = 20;
    public static final int maxTextSize = 500;

    public static void main(String[] args){

        //assign variables
        String userHandle, clientHandle, outgoingMessage, incomingMessage;
        int port;
        boolean continueLoop = true;//used as flag to signal when loop should end
        Scanner input = new Scanner(System.in);

        //verify user gave port
        if (args.length > 0){
            port = Integer.parseInt(args[0]);
        }
        else{
            System.out.println("You need to include a port number");
            return;
        }

        //get handle
        System.out.print("Input handle: ");
        userHandle = input.nextLine();
//        input.nextLine();

        try (
                ServerSocket serverSocket = new ServerSocket(port);//start listening
        ){
            while(true){
                System.out.println("Server is ready to receive on port " + port);
                Socket clientSocket = serverSocket.accept();//accept connection
                System.out.println("Connection from " + clientSocket.getRemoteSocketAddress());
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);//read from socket
                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));//write to socket

                System.out.print("Connection Established With: ");
                incomingMessage = null;
                try{
                    clientHandle = in.readLine();//get client handle
                    System.out.println(clientHandle);//print client handle
                    out.println(userHandle);//send handle to client
                    incomingMessage = in.readLine();//receive first message
                    while (incomingMessage != null){//continue to cycle until exit command recieved from client
                        if(isExitCall(incomingMessage) == true){
                            break;
                        }
                        System.out.println(clientHandle + ":" + incomingMessage);//print incoming message
                        System.out.print(userHandle + ">");//get outgoing message
                        outgoingMessage = input.nextLine();
                        out.println(outgoingMessage);
                        if (outgoingMessage.equals("\\quit")){//check if outgoing message is quit command
                            System.out.println(clientHandle + " left the chat");
                            break;
                        }
                        incomingMessage = in.readLine();//get next message
                    }
                }
                catch (Exception e){
                    e.printStackTrace();
                }

                out.close();//close writers and socket
                in.close();
                clientSocket.close();
            }
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    //this function checks to see if exit call is received
    public static boolean isExitCall(String incomingMessage){

        String sub = "";
        for (int i = 0; i < incomingMessage.length(); i++){//cycle through to remove garbage chars from shorter messages

            if(incomingMessage.charAt(i) == '\n'){
                break;
            }
            if((int) incomingMessage.charAt(i) >= 32 && (int)incomingMessage.charAt(i) <= 126){//make sure char is valid
                sub = sub + incomingMessage.charAt(i);
            }
        }
        return sub.equals("\\quit");//return quit command if needbe
    }

}