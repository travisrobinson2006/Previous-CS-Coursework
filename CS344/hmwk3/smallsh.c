//Travis Robinson
//CS344
//Program 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
void catchint(int signo)//signal numbers courtesy of https://en.wikipedia.org/wiki/Unix_signal#POSIX_signals
{//using write to avoid re-entrancy
	char * output_text;
//	printf("caught interrupt\n");
	if (signo == 6)
	{
		output_text = "terminated by signal 6\n";
	}
	if (signo == 14)
	{
		output_text = "terminated by signal 14\n";
	}
	if (signo == 1)
	{
		output_text = "terminated by signal 1\n";
	}
	if (signo == 2)
	{
		output_text = "terminated by signal 2\n";
	}
	if (signo == 9)
	{
		output_text = "terminated by signal 9\n";
	}
	if (signo == 3)
	{
		output_text = "terminated by signal 3\n";
	}
	if (signo == 15)
	{
		output_text = "terminated by signal 15\n";
	}
	
	write(1,output_text,strlen(output_text)); 
}

void exitFunction(int arraySize,char *args[],int number_backgrounds, int background_pids[]);//function ends all sleeping functions and ends shell
int change_directory(char *go_to);//changes directory
int main()
{
	struct sigaction act;//used for signal handling ^C
//	act.sa_handler = catchint;
	act.sa_flags = 0;
	sigfillset(&(act.sa_mask));
	act.sa_handler = catchint;//let catchint handle for parents, will have children ignore
//	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);

	int errno;//used for catching error when children sent signals
	int status = -6171985;//status set to this value to print error message if status called before any other calls made
	int status_background_check;//used to not clear status of foreground when checking on background children

	
	char command[2048];//read in from command line
	char current_working_directory[1024];//directory that we are in, used for change directory to append to path
//	char original_working_directory[1024];//directory that smallsh is located in; so we know where to return; this value no longer needed

	int max_number_arguments = 512;//leave an extra one so that NULL can be passed to tell exec end or params
	char *arguments[max_number_arguments + 1];

	int background_indicator = 0;//used to signal determine if child process should be waited for  
	int number_backgrounds = 1024;//arbitrary but large number to check on child processes
	int background_pids[number_backgrounds];//collection of child processes, used on exit to ensure that all kids are dead
	
	pid_t spawnpid;//spawn
	pid_t background_pid;//used for checking on background spawn	

	int i = 0;//initialize to 0 array of background pids
	while (i < number_backgrounds)
	{
		background_pids[i] = 0;
		i++;
	}
	
	i = 0;//allocate space for args, use 2048 because that is as large as command line will be, possible for one command to be that big
	while (i < max_number_arguments)
	{
		arguments[i] = (char*) malloc(2048);
		int j = 0;
		i++;
	}
	


//	getcwd(original_working_directory,sizeof(original_working_directory));commented out because never used
	getcwd(current_working_directory,sizeof(current_working_directory));

	printf(": ");//user prompt
	fflush(stdout);
	strncpy(command,"\0",sizeof(command));
	
	if (fgets(command,sizeof(command)-1,stdin) == NULL)//ensure it's not null, which can happen on signals being passed in
	{
		printf(": ");
		fflush(stdout);
		fgets(command,sizeof(command)-1,stdin);//leave space for terminating character
	}



//	fgets(command,sizeof(command)-1,stdin);

	while (command[0] == '\n')//ask for more prompt if user hits enter 
	{
		printf(": ");
		fflush(stdout);
		fgets(command,sizeof(command)-1,stdin);
	}	
	command[strcspn(command,"\n")] = '\0';//replace \n w/ \0 because fgets includes whitespace

// failure

	while (1)//continue to accept commands as long as it's not exit command
	{
		command[strcspn(command,"\n")] = '\0';

		if(strcmp(command,"exit") == 0)//check if it's exit, if so call on exit function
		{
			exitFunction(max_number_arguments,arguments,number_backgrounds,background_pids);
		}	

		else//if not exit, break it apart and see what it is
		{
			char* token = strtok(command," \n");
			if (token[0] == '#')//check if it's a comment
			{
				//do nothing
			}


			else if (strcmp(token,"cd") == 0)//move to desired directory, calling on change directory function
			{
				token = strtok(NULL," \n");//get where directory desired is
				int successful = change_directory(token);//pass to path function, print error if failed to change directory
				if (successful == 0)//print error message
				{
					//error message here
					printf("failed to change directory\n");	
					fflush(stdout);
				}
			}
			else if (strcmp(token,"status") == 0)//check on status of last foreground
			{
				if (status == -6171985)//value status initialized to, checks to see if prior commandds exist
				{
					printf("no prior commands completed\n");
					fflush(stdout);
				}
				else
				{
					if (WIFEXITED(status))//exit normally
					{
						int exitstatus = WEXITSTATUS(status);
						printf("exit value %d\n",exitstatus);
						fflush(stdout);
					}
					else//or exit with signal
					{
						printf("terminated by signal %d\n",status);
						fflush(stdout);
					}
				}
			}
			else //non-built in commands here
			{
				strncpy(arguments[0],token,strlen(token));
				char input_file_name[2048];//input file
				char output_file_name[2048];//output file
				int fd_input;//for parent
				int fd_input2;//for dup2
				int fd_output;//for parent
				int fd_output2;//for dup2
				int redirect_input = 0;//flag for whether or not input file used
				int redirect_output = 0;//flag to say if output file used
				background_indicator = 0;//set background to default of foreground

				i = 1;//i starts at 1 to make sure initial token at 0 isn't overridden
				token = strtok(NULL," \n");
				while(token != NULL)
				{
					if (token[0] == '#')//if it's a comment, don't do anything else with what's left
					{
						break;
					}	
					if (strcmp(token,"<") == 0 || strcmp(token,">") == 0 || strcmp(token,"&") == 0)//special instructions for input/output files or background indicator
					{ 
						if (strcmp(token,"<") == 0)//input file
						{
							token = strtok(NULL," \n");//move to name of input file
							strncpy(input_file_name,token,strlen(token));//copy input file name from token
							redirect_input = 1;//set flag so we can tell fork to redirect before exec
						}
						if (strcmp(token,">") == 0)//output file
						{
							token = strtok(NULL," \n");//move to name of file from command line
							strncpy(output_file_name,token,strlen(token));
							redirect_output = 1;//set flag to tell fork to redirect output
						}
						if (strcmp(token,"&") == 0)//run in backgroung
						{
							background_indicator = 1;//set background flag to tell parent not to wait for this chi
						}
					}
					else// (token != NULL)//prevent file redirects from causing a segfault,//no longer valid, stuff in comments 
							  //so strncpy only done of next token  is not null 
					{
						strcpy(arguments[i],token);//use str instead of strn due to problems with extra values being added to end affecting directory creation
						i++;
					}
					token = strtok(NULL," \n");
				}
				
				char *temp = arguments[i];//use temp to restore string after null passed
				arguments[i] = NULL;//set argument to NILL  for use of exec, so it knows when to stop

			
				spawnpid = fork();

				struct sigaction act;//for child
//				act.sa_handler = catchint;
				act.sa_flags = 0;
				sigfillset(&(act.sa_mask));

				if(spawnpid <= -1)//error forking
				{
					printf("forking error\n"); 
					fflush(stdout);
					exit(1);
				}
				else if (spawnpid == 0)
				{
					if (redirect_input == 1)
					{
						fd_input = open(input_file_name, O_RDONLY);//open file indicator and childs redirect, input
						fd_input2 = dup2(fd_input,0);
					}
					else if (redirect_input == 0 && background_indicator == 1)//if no file provided and a background pid, then need to get from null to not stop user
					{
						fd_input = open("/dev/null",O_RDONLY);
						fd_input2 = dup2(fd_input,0);
					}
					if (redirect_output == 1)//open file indicator and child redirect, output
					{
						fd_output = open(output_file_name,O_WRONLY|O_CREAT|O_TRUNC, 0777);
						if (fd_output == -1)
						{
							perror("open");//make sure no errors opening
							exit(1);
						}
						fd_output2 = dup2(fd_output,1);
						if (fd_output2 == -1)
						{
							perror("dup2");
							exit(2);
						}
					}
					else if (redirect_output == 0 && background_indicator == 1)//redirect to null if a background and if no output given
					{
						fd_output = open("/dev/null",O_WRONLY);
						if (fd_output == -1)//make sure no errors opening
						{
							perror("open");
							exit(1);
						}
						fd_output2 = dup2(fd_output,1);
						if (fd_output2 == -1)
						{
							perror("dup2");
							exit(2);
						}
	
					}
					if (fd_input == -1)//print error message if user inputs bad file input, then exit with error code
					{
						
						printf("smallsh: cannot open %s for input\n",input_file_name);
						fflush(stdout);
						exit(1);
					}
					else
					{
						if (background_indicator == 0)//set so ^C ends foreground process
						{
							act.sa_handler = SIG_DFL;
							sigaction(SIGINT, &act, NULL);
						}
						else if (background_indicator == 1)//if it's a background, ignore it
						{
							act.sa_handler = SIG_IGN;
							sigaction(SIGINT, &act, NULL);
						}
						else
						{
							printf("unforseen behavior\n");//ensure that I don't do something that isn't 0 or 1
							fflush(stdout);
						}
						execvp(arguments[0],arguments);//start new program with redirected input, having killed fork
						printf("%s: no such file or directory\n",arguments[0]);//if no program exists, alert user and kill fork
						fflush(stdout);
						exit(1);
					}
				}
				else //parent process
				{
					act.sa_handler = catchint;//use signal catcher if parent process
					sigaction(SIGINT, &act, NULL);
					if (background_indicator == 0)//foreground process, we want to wait for it
					{
						do//wait for foreground, keep waiting until properly killed by signal or it dies naturally 
						{
							spawnpid = waitpid(spawnpid,&status,0);
						}
						while (spawnpid == -1 && errno == EINTR);//keep looking until we get signal back, else shell is killed too
						if (spawnpid == -1)
						{
							perror("there was a failure\n");
							exit(1);
						}
					}
					else if (background_indicator == 1)//don't wait for process
					{
						int j = 0;
						while (j < number_backgrounds)
						{
							if(background_pids[j] == 0)//assign background pid to array for checking on at exit
							{
								background_pids[j] = spawnpid;
								break;
							}	
							j++;
						}
						printf ("background pid is %d\n",spawnpid);//tell user what pid for background is, as per prog requirements
						fflush(stdout);
						if (spawnpid == -1)
						{
							perror("there was a failure\n");
							exit(1);
						}
					}
				} 
				arguments[i] = temp;//null passed, restore string
				i = 0;

				while (i < max_number_arguments)//clear arguments so eleminate accidental leftovers w/ future commands
				{
					strncpy(arguments[i],"\0",sizeof(arguments[i]));
					i++;
				}
				close(fd_input);//close files, reset flags
				close(fd_output);
				redirect_input = 0;
				redirect_output = 0;
			}
		}

		spawnpid = waitpid(-1,&status_background_check,WNOHANG); //check if a process is done
				i = 0;//reset dead pids to 0 for element reuse in array
				while (i < number_backgrounds)
				{
					if (background_pids[i] == spawnpid)
					{
						background_pids[i] == 0;
					}
					i++;
				} 
				
		while (spawnpid != 0 && spawnpid != -1)//do stuff in loop until no more processes are done
		{
			if (WIFSIGNALED(status_background_check))//check if killed by signal
			{
				i = 0;//reset dead pids to 0 for element reuse in array
				while (i < number_backgrounds)
				{
					if (background_pids[i] == spawnpid)
					{
						background_pids[i] == 0;
					}
					i++;
				} 
				int exitstatus = WTERMSIG(status_background_check);//print terminating signal
				printf("background pid %d is done: terminated by signal %d\n",spawnpid,exitstatus);
				fflush(stdout);
			}
			else if (WIFEXITED(status_background_check))//otherwise died a natural death 
			{
				i = 0;//clear elements that are no longer needed
				while (i < number_backgrounds)
				{
					if (background_pids[i] == spawnpid)
					{
						background_pids[i] == 0;
					}
					i++;
				} 
				int exitstatus = WEXITSTATUS(status_background_check);//print exit status
				printf("background pid %d is done: exit value %d\n",spawnpid,exitstatus);
				fflush(stdout);
			}
			spawnpid = waitpid(-1,&status_background_check,WNOHANG); //move to next spawn or be stuck in loop
		}	

		background_indicator = 0;//reset default value	
		printf(": ");//print new line for user input
		fflush(stdout);
		strncpy(command,"\0",sizeof(command));//clear command
//		fgets(command,sizeof(command)-1,stdin);
		if (fgets(command,sizeof(command)-1,stdin) == NULL)//make sure it's not NULL if user hits ^C, otherwise we ask again
		{
			printf(": ");
			fflush(stdout);
			fgets(command,sizeof(command)-1,stdin);
		}
		while (command[0] == '\n')//if user hits enter w/out putting anything down
		{
			printf(": ");
			fflush(stdout);
			fgets(command,sizeof(command)-1,stdin);
		}	
	}


	exit(0);
}
//exits shell
//kills any kids that aren't already dead
void exitFunction(int arraySize,char *args[],int number_backgrounds, int background_pids[])
{
	pid_t spawnpid;//used to fork command
	args[0] = "kill";//create kill command for children
	args[1] = "-15";
	args[3] = NULL;
	int i = 0;
	while (i < number_backgrounds)//go through all kids still in background and array and kill them
	{
		if(background_pids[i] != 0)
		{
	//		printf("skipped one");//used for testing
			fflush(stdout);
			sprintf(args[2],"%d",background_pids[i]);
			spawnpid = fork();//fork and send in kill command
			if(spawnpid <= -1)
			{
				printf("there was a forking error\n"); 
				fflush(stdout);
				exit(1);
			}
			else if (spawnpid == 0)
			{
				execvp(args[0],args);
			}
		}
		i++;
	}

	exit(0);//successfully exited
}

//this function returns 1 if change directory successful, 0 otherwise
//changes current working directory
int change_directory(char *go_to)
{
	int successful;
	char current_working_directory[1024];
	if ( go_to == NULL)//user didn't specify a path, go to home directory
	{
		successful = chdir(getenv("HOME"));//path to home directory
	}
				
	else
	{
		getcwd(current_working_directory,sizeof(current_working_directory));//get current directory to append path addition onto
		strncat(current_working_directory,"/",sizeof(current_working_directory)-sizeof("/"));//append / for path
		strncat(current_working_directory,go_to,sizeof(current_working_directory)-sizeof(go_to));//append directory to add to path
		successful = chdir(current_working_directory);//check  if changing directory was successful
	}
	if(successful == 0)//return yes if change was successful, say no otherwise
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




