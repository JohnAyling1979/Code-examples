/***********************************************************
CSCI 480 - Assignment 1 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: September 6, 2017

Purpose: This program calls two forks and shows the pid
associated to the processes
************************************************************/
#include<iostream>
#include<cstdlib>
#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    int pid;

    //displays info about the first process
    cout<<"I am the original process. My PID is "<<getpid();
    cout<<" and my parent's PID is "<<getppid()<<endl;

    //first fork
    cout<<"Now we have the first fork."<<endl;
    pid=fork();

    //error check
    if(pid==-1)
    {
        cerr<<"The first fork failed."<<endl;
        exit(-1);
    }

    //child path
    if(pid==0)
    {
        cout<<"I am the child. My PID is "<<getpid();
        cout<<" and my parent's PID is "<<getppid()<<endl;

	//second fork
        cout<<"Now we have the second fork."<<endl;
        pid=fork();

        //error check
        if(pid==-1)
        {
            cerr<<"The second fork failed."<<endl;
            exit(-1);
        }

        //grandchild path
        if(pid==0)
        {
            cout<<"I am the grandchild. My PID is "<<getpid();
            cout<<" and my parent's PID is "<<getppid()<<endl; 
            cout<<"I am the grandchild, about to exit."<<endl;
            exit(0);
        }
        //child path
        else
        {
            cout<<"I am still the child. My PID is "<<getpid();
            cout<<" and my parent's PID is "<<getppid()<<endl; 
            wait(0);
            cout<<"I am the child, about to exit."<<endl;
            exit(0);
        }

    }
    //parent path
    else
    {
        cout<<"I am the parent. My PID is "<<getpid();
        cout<<" and my parent's PID is "<<getppid()<<endl;
        sleep(2);
        cout<<"I am the parent, about to call ps."<<endl;
        system("ps");
        wait(0);
        cout<<"I am the parent, about to exit."<<endl;
        exit(0);
    }
}
