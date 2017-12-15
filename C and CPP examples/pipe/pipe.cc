/***********************************************************
CSCI 480 - Assignment 2 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: September 6, 2017

Purpose: To use pipe() to send information between processes
************************************************************/
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<cstring>

using namespace std;

void loop(int[],int[],string);
void PWork(int[],int[]);
void CWork(int[],int[]);
void GWork(int[],int[]);

int main()
{
	//[0] read from [1] write to
	int PipeA[2],PipeB[2],PipeC[2];

	//creates the three pipes
	if(pipe(PipeA)==-1)
	{
		cerr<<"pipe #1 error"<<endl;
		exit(-5);
	}
	if(pipe(PipeB)==-1)
	{
		cerr<<"pipe #2 error"<<endl;
		exit(-5);
	}
	if(pipe(PipeC)==-1)
	{
		cerr<<"pipe #3 error"<<endl;
		exit(-5);
	}

	//first fork
	switch(fork())
	{
		//error case
		case -1:
		cerr<<"fork #1 error"<<endl;
		exit(-5);

		//child case
		case 0:
		//second folk
		switch(fork())
		{
			//error case
			case -1:
			cerr<<"fork #2 error"<<endl;
			exit(-5);

			//grandchild
			case 0:
			close(PipeA[0]);
			close(PipeA[1]);
			close(PipeB[1]);
			close(PipeC[0]);
			GWork(PipeB,PipeC);
			close(PipeB[0]);
			close(PipeC[1]);
			exit(0);

			//child
			default:
			close(PipeA[1]);
			close(PipeB[0]);
			close(PipeC[0]);
			close(PipeC[1]);
			CWork(PipeA,PipeB);
			close(PipeA[0]);
			close(PipeB[1]);
			wait(0);
			exit(0);
		}

		//parent
		default:
		close(PipeC[1]);
		close(PipeB[0]);
		close(PipeB[0]);
		close(PipeA[0]);
		PWork(PipeC,PipeA);
		close(PipeC[0]);
		close(PipeA[1]);
		wait(0);
		exit(0);
	}
	return 0;
}

/***************************************************************
loop

Use: Is the main loop that is ran by all three processes

Parameters: 1.	rPipe[]: An array containing the pipe for
				the in connection
            2.	wPipe[]: An array containing the pipe for
				the out connection
			3.	proc   : Contains the process sting for display

Returns: nothing
***************************************************************/
void loop(int rPipe[],int wPipe[],string proc)
{
	char Buffer[10],Value[10]={'1','\0'};
	int loc;
	int M=1;

	//main loop that runs till M=99999999
	while(M<=99999999)
	{
		//read characters from the pipe untill '\0' is read
		for(read(rPipe[0],&Value[0],1),loc=1;Value[loc-1]!='\0';read(rPipe[0],&Value[loc],1),loc++);

		//change to int and perform calculation
		M=atoi(Value);
		M=4*M+3;

		//change int back to char[]
		sprintf(Buffer,"%d",M);

		//print to screen
		cerr<<proc<<"	Value =  "<<M<<endl;

		//sends Value to next process
		write(wPipe[1],Buffer,strlen(Buffer)+1);
	}
	return;
}

/***************************************************************
PWork

Use: process ran by the parent

Parameters: 1.	rPipe[]: An array containing the pipe for
				the in connection
            2.	wPipe[]: An array containing the pipe for
				the out connection

Returns: nothing
***************************************************************/
void PWork(int rPipe[],int wPipe[])
{
	//prints the starting value
	cerr<<"Parent:		Value =  1"<<endl;

	//sends first value to the child
	write(wPipe[1],"1",2);

	//call read and write loop
	loop(rPipe,wPipe,"Parent:\t");

	return;
}

/***************************************************************
CWork

Use: process ran by the child

Parameters: 1.	rPipe[]: An array containing the pipe for
				the in connection
            2.	wPipe[]: An array containing the pipe for
				the out connection

Returns: nothing
***************************************************************/
void CWork(int rPipe[],int wPipe[])
{
	//call read and write loop
	loop(rPipe,wPipe,"Child:\t");

	return;
}

/***************************************************************
GWork

Use: process ran by the parent

Parameters: 1.	rPipe[]: An array containing the pipe for
				the in connection
            2.	wPipe[]: An array containing the pipe for
				the out connection

Returns: nothing
***************************************************************/
void GWork(int rPipe[],int wPipe[])
{
	//call read and write loop
	loop(rPipe,wPipe,"Grandchild:");

	return;
}
