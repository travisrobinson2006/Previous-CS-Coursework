//Travis Robinson
//CS344
//Program 2


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> //for random numbers
#include <string.h> //for length of string functions

int main(void)
{
	srand(time(NULL));//seed random number

	const int number_of_rooms = 7; //number of rooms stored as const for ease of changing

	//struct containing room names and room availability
	struct room_names {
	char *name;//name of room
	int name_taken;//bool value to determine if number is still available
	};

	//struct containing room info; name,connections,number of connections,etc
	struct room_data {
	char *name;//room name
	int number_connections;//number of connections, randomly assigned and later counted due to later rooms reconnecting to earlier ones
	char *connections[6]; //array of connections
	char *room_type;//ie start, mid or end
	};

	//array of ints for tracking which rooms are used
	//used to prevent a room from connecting to the same room multiple times
	int room_tracker[number_of_rooms];
	int i = 0;
	while (i < number_of_rooms)
	{
		room_tracker[i] = 0;
		i++;
	}

	//create directory
	char directory[25];
	sprintf(directory,"robitrav.rooms.%d",getpid());
	mkdir(directory,0777);

	//assign room names to rooms
	int file_descriptor;
	char file_name[40]; 
	char input_text[2048];//large value used in case user takes a while finding end room
	strncpy(input_text,"\0",sizeof(input_text));

	//create room names
	struct room_names list_of_names[10];
	list_of_names[0].name="MalcolmReynolds";
	list_of_names[0].name_taken = 0;
	list_of_names[1].name="ZoeWashburn";
	list_of_names[1].name_taken = 0;
	list_of_names[2].name="HobanWashburne";
	list_of_names[2].name_taken = 0;
	list_of_names[3].name="InaraSerra";
	list_of_names[3].name_taken = 0;
	list_of_names[4].name="JayneCobb";
	list_of_names[4].name_taken = 0;
	list_of_names[5].name="KayleeFrye";
	list_of_names[5].name_taken = 0;
	list_of_names[6].name="SimonTam";
	list_of_names[6].name_taken = 0;
	list_of_names[7].name="RiverTam";
	list_of_names[7].name_taken = 0;
	list_of_names[8].name="DerrialBook";
	list_of_names[8].name_taken = 0;
	list_of_names[9].name="Serenity";
	list_of_names[9].name_taken = 0;


	//set room data
	struct room_data rooms[number_of_rooms];

	//initialize connections, connections of all rooms set to \0
	i = 0;
	while (i < number_of_rooms)
	{
		int j = 0;
		while (j < 6)
		{
			rooms[i].connections[j] = "\0";
			j++;
		}
		i++;
	}


	i = 0;
	while (i < number_of_rooms)
	{
		int randomName = rand() % number_of_rooms;//assign random number to get name from array
		while (list_of_names[randomName].name_taken == 1) //if name is taken, move to next name
		{
			randomName++;
			if (randomName > 9) //if end of array reached, move to beginning
			{
				randomName = 0;
			}
			
		}
		list_of_names[randomName].name_taken = 1;//mark room as no longer available
		rooms[i].name = list_of_names[randomName].name;
//		printf("%s",rooms[i].name);
		i++;
	}
	i = 0;
	while (i < number_of_rooms)
	{
		int number_connections;
		if (i < 3) //limit number of connections for first rooms to prevent rooms from forming too many connections
				//will still be random due to later rooms being able to connect to earlier rooms
		{
			number_connections = rand() % 2;
			number_connections = number_connections + 3;
		}
		else//allow full range for later rooms
		{
			number_connections = rand() % 3;
			number_connections = number_connections + 3;
		}
		
		rooms[i].number_connections = number_connections;
		int k = 0;
		while (k < number_of_rooms)//set tracker so that when entering a room that has already been connected to an earlier room doesn't connect to that room again 
		{
			int l = 0;
			while (l < 6)
			{
				if (rooms[i].connections[l] == rooms[k].name)
				{
					room_tracker[k] = 1;
				}
				l++;
			}
			k++;
		}

		int connection_number = 0;
		while(connection_number < number_connections)
		{
			if (rooms[i].connections[connection_number] == "\0")//if a connection not formed yet, connect to another room 
			{
				int connected_to = rand() % number_of_rooms;

				//check if room already taken,connection is current room or connection has no valid connections 
				while (room_tracker[connected_to] == 1 ||  connected_to == i || rooms[connected_to].connections[5] != "\0")
				{
//		printf("searching for valid connection\n");	
					connected_to = rand() % number_of_rooms;
				}
				room_tracker[connected_to] = 1;
				rooms[i].connections[connection_number] = rooms[connected_to].name;
				//form connection back in room connected to
				int j = 0;
				while (j < 6)
				{
					if(rooms[connected_to].connections[j] == "\0")
					{
						rooms[connected_to].connections[j] = rooms[i].name;
						break;
					}
					j++;
				}



			}
			connection_number++;
		}
		//clear the tracker array for reuse
		int clear_tracker = 0;
		while (clear_tracker < number_of_rooms)
		{
			room_tracker[clear_tracker] = 0;
			clear_tracker++;
		}

		i++;
	}
	i = 0;
/*	while (i < rooms[0].number_connections)
	{
		printf("%s\n",rooms[0].connections[i]);
		i++;
	}
*/

	//reread connections to find actual number, since it may have changed with
	//rooms connection to prior rooms
	i = 0;
	while (i < number_of_rooms)
	{
		int j = 0;
		while(rooms[i].connections[j] != "\0" && j < 6)
		{
			j++;
		}
		rooms[i].number_connections = j;	
		i++;
	}

	//assign start room and end room, all others are mid rooms
	int start_room = rand() % 7;//randomly assign start
	int end_room = rand() % 7;//randomly assign end
	while (end_room == start_room)//make sure end != start
	{
		end_room = rand() % 7;
	}
	i = 0;
	while (i < number_of_rooms)
	{
		if (i == start_room)
		{
			rooms[i].room_type = "START_ROOM";
		}
		else if (i == end_room)
		{
			rooms[i].room_type = "END_ROOM";
		}
		else
		{
			rooms[i].room_type = "MID_ROOM";
		}
		i++;
	}


	//read room data into room files
	i = 0;
	while (i < number_of_rooms)
	{
		sprintf(file_name,"%s/room%d",directory,i);
		file_descriptor = open(file_name,O_WRONLY | O_CREAT, 0777);
		sprintf(input_text,"ROOM NAME: %s\n",rooms[i].name);//write in name of room
		write(file_descriptor,input_text,strlen(input_text));
		strncpy(input_text,"\0",sizeof(input_text));//clear input text so it doesn't include past data
		int j = 0;	
		while (j < rooms[i].number_connections)//write in connections
		{
			sprintf(input_text,"CONNECTION %d: %s\n",j,rooms[i].connections[j]);
			write(file_descriptor,input_text,strlen(input_text));
			j++;
		}
		strncpy(input_text,"\0",sizeof(input_text));
		sprintf(input_text,"ROOM TYPE: %s",rooms[i].room_type);//write in satart, end mid
		write(file_descriptor,input_text,strlen(input_text));
		strncpy(input_text,"\0",sizeof(input_text));
		i++;
	}
	strncpy(input_text,"\0",sizeof(input_text));
	
	close(file_descriptor);

	//clear room data for reading
	//to save space on computer,the same array will be used for writing to and reading from files
	i = 0;
	while(i < number_of_rooms)
	{
		rooms[i].name="\0";//delete room name
		rooms[i].number_connections = 0;//reset number connections
		rooms[i].room_type="\0";//delete room type
		int j = 0;//clear connections
		while(j < 6)
		{
			rooms[i].connections[j]="\0";
			j++;
		}
		i++;
	}


	//read data from files
	i = 0;
	while (i < number_of_rooms)
	{
		sprintf(file_name,"%s/room%d",directory,i);//copy in file names containing room data
		file_descriptor = open(file_name,O_RDONLY);
		strncpy(input_text,"\0",sizeof(input_text));
		read(file_descriptor,input_text,sizeof(input_text));
		char* token = strtok(input_text, ":");//start tokenizing
		while (token != NULL)
		{
			if (strcmp("ROOM NAME",token) == 0)//first token w/ : as delim will be room name, we want the one after that
			{
				token = strtok(NULL," \n");//take another token, using space as token to get the name of the room
				rooms[i].name =  malloc(40*sizeof(char));//assign storage for room name (before was pointing at location of original string in the potential names
				strcpy(rooms[i].name,token);
			}
			else if (strcmp("CONNECTION",token) == 0)//looking for the connection tokens
			{
				token = strtok(NULL,":");//move past the : to get to the connection name 
				rooms[i].number_connections++;
				token = strtok(NULL,": \n ");//this is the token with the name of the connection in it
				int k = 0;
				while (k < rooms[i].number_connections)//increment through connections until we find one that's available
				{
					if (rooms[i].connections[k] == "\0")
					{
						rooms[i].connections[k] = malloc(40*sizeof(char));//assign space for connection name; before was pointing at original name
						strcpy(rooms[i].connections[k],token);
						k++;
						break;
					}
					else
					{
						k++;
					}
				}
			}
			else if (strcmp("ROOM",token) == 0)//finding token for room type. Type is preceded by "ROOM TYPE" phrase
			{
				token = strtok(NULL,":");
				token = strtok(NULL," :");//skipping TYPE to get to the room type word
				rooms[i].room_type = malloc(20*sizeof(char));//allocate space for room type
				strcpy(rooms[i].room_type,token);
			}

			token = strtok(NULL," \n");
		}
		i++;
		close(file_descriptor);
	}
	i = 0;
/*	while (i < number_of_rooms)
	{
		printf("Room %d: %s:\n",i,rooms[i].name);
		int k = 0;
		while(k < 6)
		{
			printf("Connection %d: %s\n",k,rooms[i].connections[k]);
			k++;
		}
		printf("Room Type: %s:\n",rooms[i].room_type);
		
		i++;
	}
*/
	//make the interface!!!!
	//and navigate the game
	
	//find starting location
	int current_location;//use this value to remember what room we're in
	i = 0;
	while (i < number_of_rooms)//loop through to find the starting one
	{
		if (strcmp(rooms[i].room_type,"START_ROOM") == 0)
		{
			current_location = i;
			break;
		}
		i++;
	}

	//find end location
	int end_location;//loop through to find the ending room
	i = 0;
	while (i < number_of_rooms)
	{
		if (strcmp(rooms[i].room_type,"END_ROOM")==0)
		{
			end_location = i;
			break;
		}
		i++;
	}

	//print interface, repeat until end room, tracking number of steps and route taken
	int step_count = 0;//will track number of steps taken
	sprintf(file_name,"%s/room%s",directory,"adventure_temp");//file used to track path
	file_descriptor = open(file_name,O_WRONLY | O_CREAT, 0777);

	//prepare to write names to file, write starting room name //don't do after rereading project req's
/*	strncpy(input_text,"\0",sizeof(input_text));
	sprintf(input_text,"%s\n",rooms[current_location].name);
	write(file_descriptor,input_text,strlen(input_text));
	strncpy(input_text,"\0",sizeof(input_text));*/


	while (current_location != end_location)//stop when end room found
	{
	//	printf("%d\n",current_location);
	
		printf("\nCURRENT LOCATION: %s\n",rooms[current_location].name);
		
		strncpy(input_text,"\0",sizeof(input_text));

		i=0;
		while(strcmp(rooms[current_location].connections[i],"\0")!= 0 && i < 6 )//print available connections
		{
			strcat(input_text,rooms[current_location].connections[i]);
			if (strcmp(rooms[current_location].connections[i+1],"\0") == 0 || i == 5)//if these conditions, last connection made and print a period instead of comma
			{
				strcat(input_text,".");
				break;
			}
			strcat(input_text,", ");//add comma to end of room name
			i++;
		}
		printf("POSSIBLE CONNECTIONS: %s\n",input_text);
		strncpy(input_text,"\0",sizeof(input_text));

		printf("WHERE TO? >");
		scanf("%s",&input_text);//accept user input string for where they want to go

		i = 0;
		int invalid_room = 0;//invalid room name flag
		while (i < 6)
		{
			if (strcmp(rooms[current_location].connections[i],input_text) == 0)//verify that entered room name is on the list of connections
			{
				int k = 0;
				while (k < number_of_rooms)//sort through rooms to find the one that is a valid connection entered by user
				{
					if(strcmp(rooms[k].name,input_text) == 0)
					{
						current_location = k;//update location
						strncpy(input_text,"\0",sizeof(input_text));//clear text
						sprintf(input_text,"%s\n",rooms[current_location].name);//print room name to temp file used dfor stroing names
						write(file_descriptor,input_text,strlen(input_text));
						strncpy(input_text,"\0",sizeof(input_text));//clear text again
						step_count++;//update step count
						break;//end loop to go back to outer loop
					}
					k++;
				}
				break;
			//current connection nul(all after will be too) or end of possible connections
			////in this case set invalid room flag
			}
			else if (strcmp(rooms[current_location].connections[i],"\0") == 0 || i == 5)
			{
//				printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN\n");
				invalid_room = 1;
			}
			i++;
		}  
		
		if (invalid_room != 0)//print error, go back to beginning if invalid input provided
		{
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN\n");
			
		}




	}

	close(file_descriptor);

	sprintf(file_name,"%s/room%s",directory,"adventure_temp");
	file_descriptor = open(file_name,O_RDONLY);
	strncpy(input_text,"\0",sizeof(input_text));//copy in path, this is reason input_text is so big, to ensure sufficient space
	read(file_descriptor,input_text,sizeof(input_text));
	
	printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n",step_count);
	
	printf("%s",input_text);
	fflush(stdout);
	close(file_descriptor);

	remove(file_name);//delete temp file





	exit(0);

}
