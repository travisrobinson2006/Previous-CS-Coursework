//Travis Robinson
//CS344
//Program 5
//Keygen.c

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int keyLength;//length of key
	int i;//used as a counter 
	char *key;//key itself, to be malloc'ed

	int fd;


	keyLength = atoi(argv[1]);//assign key length based on command line input
	key = (char*) malloc (keyLength+2);//+2 for terminating character and \n at end

	time_t t;//seed random number generator
	srand((unsigned int) time(&t));
//	printf("%s\n",argv[1]);


	while(i<keyLength)//assign elements to random letters
	{
		char randomLetter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "[random() % 27];//generate random letter/space
		key[i] = randomLetter;
		i++;
	}
	key[i] = '\n';
	write(1,key,strlen(key));//write to std out as per program req's
}
