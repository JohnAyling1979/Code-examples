/*****************************************************************
CSCI 480 - Assignment 5 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: October 28, 2017

Purpose: To use POSIX threads to illustrate the Producer-Consumer
Problem
*****************************************************************/
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

//assignment defined constants
#define P_NUMBER 6
#define C_NUMBER 4
#define BUFFER_SIZE 12
#define N_P_STEPS 4
#define N_C_STEPS 6

using namespace std;

//global variables
pthread_mutex_t mutex;
sem_t NotFull,NotEmpty;
int Counter=0;

//function headers
void* Produce(void*);
void Insert(long);
void* Consume(void*);
void Remove(long);

int main()
{
	//title
	cout<<"Simulation of Producer and Consumers"<<endl<<endl;

	//program threads
	pthread_t produce[P_NUMBER];
	pthread_t consume[C_NUMBER];

	//return code
	int rc;

	//initializing atomic variables
	rc=pthread_mutex_init(&mutex,NULL);
	if(rc)
	{
		cerr<<"Mutex failed. Error code:"<<rc<<endl;
		exit(EXIT_FAILURE);
	}
	if(sem_init(&NotFull,0,BUFFER_SIZE))
	{
		cerr<<"NotFull semaphore failed"<<endl;
		exit(EXIT_FAILURE);
	}
	if(sem_init(&NotEmpty,0,0))
	{
		cerr<<"NotEmpty semaphore failed"<<endl;
		exit(EXIT_FAILURE);
	}

	cout<<"The semaphores and mutex have been initialized."<<endl<<endl;

	//creates the producer threads and checks for errors
	for(long i=0;i<P_NUMBER;i++)
	{
		rc=pthread_create(&produce[i],NULL,Produce,(void*)i);
		if(rc)
		{
			cerr<<"Error:Return Code from thread create is "<<rc<<endl;
			exit(EXIT_FAILURE);
		}
	}

	//creates the consumer threads and checks for errors
	for(long i=0;i<C_NUMBER;i++)
	{
		rc=pthread_create(&consume[i],NULL,Consume,(void*)i);
		if(rc)
		{
			cerr<<"Error:Return Code from thread create is "<<rc<<endl;
			exit(EXIT_FAILURE);
		}
	}

	//waits for all threads to finish
	for(int i=0;i<P_NUMBER;i++)
	{
		rc=pthread_join(produce[i],NULL);
		if(rc)
		{
			cerr<<"Error:Return Code from thread join is "<<rc<<endl;
			exit(EXIT_FAILURE);
		}
	}
	for(int i=0;i<C_NUMBER;i++)
	{
		rc=pthread_join(consume[i],NULL);
                if(rc)
                {
                        cerr<<"Error:Return Code from thread join is "<<rc<<endl;
                        exit(EXIT_FAILURE);
                }
	}

	//finished threads line
	cout<<endl<<"All the producer and consumer threads have been closed."<<endl<<endl;

	//clean up
	if(sem_destroy(&NotFull))
	{
		cerr<<"Error:Destroy of NotFull failed"<<endl;
		exit(EXIT_FAILURE);
	}
	if(sem_destroy(&NotEmpty))
        {
                cerr<<"Error:Destroy of NotEmpty failed"<<endl;
                exit(EXIT_FAILURE);
        }
	rc=pthread_mutex_destroy(&mutex);
        if(rc)
        {
		cerr<<"Error:Return Code from destroy mutex is "<<rc<<endl;
                exit(EXIT_FAILURE);
	}

	//cleanup line
	cout<<"The semaphores and mutex have been deleted."<<endl<<endl;

	//exit main thread
	pthread_exit(NULL);
}

/***************************************************************
Produce

Use: to be the start routine for a thread

Parameters: 1.  void* threadid: the id number used in the
		create thread function

Returns: nothing
***************************************************************/
void* Produce(void* threadid)
{
	//converts id to a long
	long id=(long)threadid;

	//repeat a given number of times
	for(int i=0;i<N_P_STEPS;i++)
	{
		//waits if full
		if(sem_wait(&NotFull))
		{
			cerr<<"Wait for NotFull failed"<<endl;
			exit(EXIT_FAILURE);
		}

		//inserts item
		Insert(id);
//		sleep(1);

		//increases atomic counter of full spaces
		if(sem_post(&NotEmpty))
                {
                        cerr<<"Adding to NotEmpty failed"<<endl;
                        exit(EXIT_FAILURE);
                }
	}
	//thread end
	pthread_exit(NULL);
}

/***************************************************************
Insert

Use: to insert a pretend widget into a pretend buffer

Parameters: 1.  long id: the id number that was assigned to the
		thread

Returns: nothing
***************************************************************/
void Insert(long id)
{
	int rc;

	//lock mutex on entering
	//if already locked will wait
	rc=pthread_mutex_lock(&mutex);
	if(rc)
	{
		cerr<<"locking error. Code: "<<rc<<endl;
		exit(EXIT_FAILURE);
	}

	//output message and increase global counter
	cout<<"Producer "<<id<<" inserted one item.  ";
	cout<<"Total is now "<<setw(2)<<++Counter<<endl;

	//unlock mutex for other thread use
	rc=pthread_mutex_unlock(&mutex);
        if(rc)
        {
                cerr<<"unlocking error. Code: "<<rc<<endl;
                exit(EXIT_FAILURE);
        }
}

/***************************************************************
Consume

Use: to be the start routine for a thread

Parameters: 1.  void* threadid: the id number used in the
                create thread function

Returns: nothing
***************************************************************/
void* Consume(void* threadid)
{
	//conver id to long
	long id=(long)threadid;

	//repeat a given number of times
	for(int i=0;i<N_C_STEPS;i++)
	{
		//wait for items
		if(sem_wait(&NotEmpty))
                {
                        cerr<<"Wait for NotEmpty failed"<<endl;
                        exit(EXIT_FAILURE);
                }

		//remove an items
		Remove(id);
//		sleep(1);

		//increase the atomic counter of empty spaces
		if(sem_post(&NotFull))
                {
                        cerr<<"Adding to NotFull failed"<<endl;
                        exit(EXIT_FAILURE);
                }
	}
	//exit thread
	pthread_exit(NULL);
}

/***************************************************************
Remove

Use: to Remove a pretend widget into a pretend buffer

Parameters: 1.  long id: the id number that was assigned to the
                thread

Returns: nothing
***************************************************************/
void Remove(long id)
{
	int rc;

	//lock mutex
	//if already locked will wair
	rc=pthread_mutex_lock(&mutex);
	if(rc)
        {
        	cerr<<"Wait for NotFull failed"<<endl;
                exit(EXIT_FAILURE);
        }

	//print message and lower global counter
	cout<<"Consumer "<<id<<" removed one item.   ";
	cout<<"Total is now "<<setw(2)<<--Counter<<endl;

	//unlock for other thread use
	rc=pthread_mutex_unlock(&mutex);
	if(rc)
        {
        	cerr<<"Wait for NotFull failed"<<endl;
        	exit(EXIT_FAILURE);
        }
}
