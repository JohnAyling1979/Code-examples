/***********************************************************
CSCI 480 - Assignment 3 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: September 26, 2017

Purpose: To make a shell program that can pipe between to
seperate programs
************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/***************************************************************
runProcess

Use: to run a given process using execvo

Parameters: 1.	char* p[]: An array containing char * to strings
		containing the separate arguments

Returns: nothing
***************************************************************/
void runProcess(char* p[])
{
	//execute process
	execvp(p[0],p);

	//will print if execv failed
	perror(p[0]);
	exit(0);
}

/***************************************************************
splitCommand

Use: To spit up the command into an array of strings

Parameters: 1.	char command[]: A char array containing muilitpe
			strings
            2.	char* p[]: An array of char* that will hold the
		seporate arguments from the command array

Returns: bool(True if a || is found) p[] will hold the values
at the end
***************************************************************/
bool splitCommand(char command[],char* p[])
{
	//inituized variables
	int place=0;
	bool found=false;

	//divide up the inputed command
	//break out if a || was found
	p[place]=strtok(command," ");
	while(p[place]!=NULL)
	{
		//if || if found set the found flag and
		//set last spot to NULL
		if(!strcmp(p[place],"||"))
		{
			found=true;
			p[place]=NULL;
			break;
		}
		//increase location and read next
		place++;
		p[place]=strtok(NULL," ");
	}

	//return true if command contained "||"
	return found;
}

int main()
{
	//read in char array and
	//10 char *
	char command[256];
	char* process[10];

	//assign memory to the area
	for(int i=0;i<10;i++)
		process[i]=(char*)malloc(256);


	//prompt and read line in
	command[0]='\n';
	do
	{
		printf("480shell>");
		scanf("%256[^\n]",command);
		getchar();
	}while(command[0]=='\n');

	//continue until q or quit is entered
	while(strcmp(command,"q") && strcmp(command,"quit"))
	{
		//split command and check if a ||
		//was found
		if(splitCommand(command,process))
		{
			//first child/second process
			switch(fork())
			{
				//fail case
				case -1:
					perror(NULL);
					exit(-1);
				//child process
				case 0:
					//for pipe
					int fd[2];

					//create pipe
					pipe(fd);

					//second child/first process
					switch(fork())
					{
						//fail
						case -1:
							perror(NULL);
							exit(-1);

						//second child/first process
                         			case 0:
							//close read from side
							close(fd[0]);

							//close stdout
							close(1);

							//set write out to stdout
							dup(fd[1]);

							//close the old duplicate
							close(fd[1]);

							//run process
							runProcess(process);

						//first child/second process
						default:
							//read the rest of the commands
							splitCommand(NULL,process);
							//close write to
							close(fd[1]);

							//close stdin
							close(0);

							//set read in to stdin
							dup(fd[0]);

							//close the old duplicate
							close(fd[0]);

							//run process
							runProcess(process);
					}
			}
		}
		//create only one child
		else
		{
			//call fork for first process
			switch(fork())
			{
				//fail case
				case -1:
					perror(NULL);
					exit(-1);
				case 0:
					//run process
					runProcess(process);
			}
		}
		//wait for child
		wait(0);

		//reprompt and read
		command[0]='\n';
		do
		{
			printf("480shell>");
			scanf("%256[^\n]",command);
			getchar();
		}while(command[0]=='\n');
	}
	return 0;
}
