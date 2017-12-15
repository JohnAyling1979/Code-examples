//start of header file
#ifndef ASSIGN4
#define ASSIGN4

//Constants per assignment
#define MAX_TIME 500
#define AT_ONCE 5
#define ARRAY_SIZE 10
#define HOW_OFTEN 25
#define PROCESS_NUMBER 97

#include<iostream>
#include<iomanip>
#include<queue>
#include<fstream>
#include<cstdlib>
#include"Process.h"

using namespace std;

//function headers
unsigned int fillReady(queue<process*>&,priority_queue<process*,vector<process*>,process>&,unsigned int,unsigned int);
void loadProcesses(queue<process*>&);
void setActive(process*&,process*&,process*&,priority_queue<process*,vector<process*>,process>&,
	priority_queue<process*,vector<process*>,process>&,priority_queue<process*,vector<process*>,process>&,unsigned int);
unsigned int cpuBurst(process*&,priority_queue<process*,vector<process*>,process>&,
	priority_queue<process*,vector<process*>,process>&,priority_queue<process*,vector<process*>,process>&,
	unsigned int&,unsigned int,unsigned int);
void  ioBurst(process*&,priority_queue<process*,vector<process*>,process>&,unsigned int,bool);
void termProcess(process*, unsigned int);
void statUpdate(process*,process*,process*,queue<process*>,priority_queue<process*,vector<process*>,process>,
	priority_queue<process*,vector<process*>,process>,priority_queue<process*,vector<process*>,process>,
	unsigned int);
void summary(unsigned int[]);

/***************************************************************
fillReady

Use: to add processes to the system

Parameters:	queue<process*> Entry: A queue holding pointers
			to all the processes
			priority_queue<process*,vector<process*>,compare> &Ready:
			pointers to processes in the ready queue
			unsigned int pCount: Number of active processes
			unsigned int Timer: current system tick

			Entry is passed by reference except Timer

Returns: number of processes in the system
***************************************************************/
unsigned int fillReady(queue<process*> &Entry,priority_queue<process*,vector<process*>,process> &Ready,
unsigned int pCount,unsigned int Timer)
{
	//while there is room and available processes
	//add them to ready queue
	while(pCount<AT_ONCE && (*Entry.front()).ArrivalTime<=Timer)
	{
		//copy mem address to ready queue
		Ready.push(Entry.front());

		//increase count
		pCount++;

		//assign start time
		(*Entry.front()).ReadyStart=Timer;
		cout<<setw(3)<<Timer<<": "<<(*Entry.front()).ProcessName<<" has moved from entry queue to ready queue "<<endl;

		//remove it from entry queue
		Entry.pop();

		//if it becomes empty break out of loop
		if(Entry.empty())
			break;
	}

	//return the currrent number of processes
	return pCount;
}

/***************************************************************
loadProcesses

Use: to assign active processes from each of the queues

Parameters:	queue<process*> Entry: A queue holding pointers
			to all the processes

			Entry is passed by reference except Timer

Returns: nothing
***************************************************************/
void loadProcesses(queue<process*> &Entry)
{
	ifstream dataIn; //input file stream
	process* processMemory; //memory space for the processes

	//open input file and check for error
	dataIn.open("data4.txt");
	if(!dataIn)
	{
		cerr<<"File failed to open"<<endl;
		exit(EXIT_FAILURE);
	}

	//allocate memory to the process
	//if no memory available exit
	processMemory=new process;
	if(processMemory==NULL)
	{
		cerr<<"Memory Error"<<endl;
		exit(EXIT_FAILURE);
	}

	//read first process
	dataIn>>(*processMemory).ProcessName;

	//read data untill process "STOPHERE" is found
	while((*processMemory).ProcessName!="STOPHERE")
	{
		dataIn>>(*processMemory).Priority;
		dataIn>>(*processMemory).ArrivalTime;
		for(int i=0;i<ARRAY_SIZE;i++)
		{
			dataIn>>(*processMemory).History[i].first;
			dataIn>>(*processMemory).History[i].second;
		}

		//load address to the entry queue
		Entry.push(processMemory);

		//allocate memory for next process
		//if no memory available
		//empty queue freeing all memory and exit
		processMemory=new process;
		if(processMemory==NULL)
		{
			cerr<<"Memory Error"<<endl;
			while(!Entry.empty())
			{
				delete Entry.front();
				Entry.pop();
			}
			exit(EXIT_FAILURE);
		}

		//ready next process
		dataIn>>(*processMemory).ProcessName;
	}

	//close input file and free last allocated  memory(STOPHERE process)
	dataIn.close();
	delete processMemory;
}

/***************************************************************
setActive

Use: to assign active processes from each of the queues

Parameters:	process* Active: a pointer to the active cpu process
			process* IActive: a pointer to the active input process
			process* OActive: a pointer to the active output process
			priority_queue<process*,vector<process*>,compare>Ready:
			A queue containing the current ready processes
			priority_queue<process*,vector<process*>,compare> Input:
			A queue containing the current input processes
			priority_queue<process*,vector<process*>,compare> Output:
			A queue containing the current output processes
			unsigned int Timer: current cycle time

			All prarameters are by reference except Timer

Returns: nothing
***************************************************************/
void setActive(process* &Active, process* &IActive, process* &OActive, priority_queue<process*,vector<process*>,process> &Ready,
priority_queue<process*,vector<process*>,process> &Input,priority_queue<process*,vector<process*>,process> &Output,unsigned int Timer)
{
	//if there is none assigned and some available
	//assign a process
	if(Active==NULL && !Ready.empty())
	{
		Active=Ready.top();
		(*Active).CPUTimer=0;
		(*Active).CPUCount++;
		cout<<setw(3)<<Timer<<": "<<(*Active).ProcessName<<" is now the active CPU process"<<endl;
		Ready.pop();
	}

	//if there is none assigned and some available
	//assign a process
	if(IActive==NULL && !Input.empty())
	{
		IActive=Input.top();
		(*IActive).IOTimer=0;
		(*IActive).ICount++;
		cout<<setw(3)<<Timer<<": "<<(*IActive).ProcessName<<" is now the active Input process"<<endl;
		Input.pop();
	}

	//if there is none assigned and some available
	//assign a process
	if(OActive==NULL && !Output.empty())
	{
		OActive=Output.top();
		(*OActive).IOTimer=0;
		(*OActive).OCount++;
		cout<<setw(3)<<Timer<<": "<<(*OActive).ProcessName<<" is now the active Output process"<<endl;
		Output.pop();
	}
}

/***************************************************************
cpuBurst

Use: to process the CPU burst

Parameters:	process* Active: a pointer to the active cpu process
			priority_queue<process*,vector<process*>,compare>Ready:
			A queue containing the current ready processes
			priority_queue<process*,vector<process*>,compare> Input:
			A queue containing the current input processes
			priority_queue<process*,vector<process*>,compare> Output:
			A queue containing the current output processes
			unsigned int finished: counts the number of finished processes
			unsigned int Timer: current cycle time
			unsigned int pCount: number of active process

			All prarameters are by reference except Timer and pCount

Returns: nothing
***************************************************************/
unsigned int cpuBurst(process* &Active, priority_queue<process*,vector<process*>,process> &Ready,
priority_queue<process*,vector<process*>,process> &Input,priority_queue<process*,vector<process*>,process> &Output,
unsigned int &finished,unsigned int Timer,unsigned int pCount)
{
	//Perform burst for this tick
        (*Active).CPUTimer++;

	//if CPU burst is done check for next burst
	if((*Active).CPUTimer==(*Active).History[(*Active).Sub].second)
	{
		//shift history index
		(*Active).Sub++;
		if((*Active).Sub==12)
		{
			cerr<<"History error: Process end was not found"<<endl;
			exit(EXIT_FAILURE);
		}

		cout<<setw(3)<<Timer<<": ";

		//update Total
		(*Active).CPUTotal+=(*Active).CPUTimer;

		//find next burst
		switch((*Active).History[(*Active).Sub].first)
		{
			case 'N':
				finished++;
				cout<<(*Active).ProcessName<<" has ended"<<endl;
				termProcess(Active,Timer);
				pCount--;
				break;
			case 'I':
				Input.push(Active);
				cout<<(*Active).ProcessName<<" has moved from ready queue to input queue"<<endl;
				break;
			case 'O':
				Output.push(Active);
				cout<<(*Active).ProcessName<<" has moved from ready queue to output queue"<<endl;
				break;
		}

		Active=NULL;
	}

	return pCount;
}

/***************************************************************
ioBurst

Use: to process the input/output burst

Parameters:	process* Active: a pointer to the active process
			priority_queue<process*,vector<process*>,compare>Ready:
			A queue containing the current ready processes
			unsigned int Timer: current cycle time
			bool input: marks it for input or output

			All prarameters are by reference except Timer and input

Returns: nothing
***************************************************************/
void ioBurst(process* &Active, priority_queue<process*,vector<process*>,process> &Ready,
unsigned int Timer,bool input)
{
	//Perform burst
        (*Active).IOTimer++;

	//if input burst is done return to ready queue
	if((*Active).IOTimer==(*Active).History[(*Active).Sub].second)
	{
		cout<<setw(3)<<Timer<<": ";
		(*Active).Sub++;

		//increase running total for input or output
		if(input)
			(*Active).ITotal+=(*Active).IOTimer;
		else
			(*Active).OTotal+=(*Active).IOTimer;

		cout<<(*Active).ProcessName<<" has moved back to ready queue"<<endl;
		Ready.push(Active);
		Active=NULL;
	}
}

/***************************************************************
termProcess

Use: to print out infomation about a process at the end of its
run

Parameters:	process* p: a pointer to a process in the process
		memory
		unsigned int time: The current time when the
		process ended used to calculate waiting time

Returns: nothing
***************************************************************/
void termProcess(process* p, unsigned int time)
{
	cout<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<"          Process Termination Stats"<<endl;
	cout<<"   Name: "<<(*p).ProcessName<<"     Priority: "<<(*p).Priority<<endl;
	cout<<"   ID : "<<setw(2)<<(*p).ProcessID<<endl;
	cout<<"   Number of bursts"<<endl;
	cout<<"   CPU: "<<setw(2)<<(*p).CPUCount<<"      Input: "<<setw(2)<<(*p).ICount<<"     Output: "<<setw(2)<<(*p).OCount<<endl;
	cout<<"   Time spent"<<endl;
	cout<<"   CPU: "<<setw(2)<<(*p).CPUTotal<<"      Input: "<<setw(2)<<(*p).ITotal<<"     Output: "<<setw(2)<<(*p).OTotal<<endl;
	cout<<"   Time spent waiting in the queues: "<<setw(3)<<time+1-(*p).CPUTotal-(*p).ITotal-(*p).OTotal-(*p).ReadyStart<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<endl;

	//release allocated memory
	delete p;
}

/***************************************************************
statUpdate

Use: to print out infomation about the system. lists active processes,
and the processes in queues

Parameters:	process* cpu: a pointer to the active cpu process
		process* in: a pointer to the active input process
		process* out: a pointer to the active output process
		queue<process*> entry: a copy of the entry  queue
		priority_queue<process*,vector<process*>,compare>ready:
			copy of the ready queue
		priority_queue<process*,vector<process*>,compare> input:
			copy of the input queue
		priority_queue<process*,vector<process*>,compare> output:
			copy of the output queue

Returns: nothing
***************************************************************/
void statUpdate(process* cpu,process* in,process* out,queue<process*> entry,priority_queue<process*,vector<process*>,process> ready,
priority_queue<process*,vector<process*>,process> input,priority_queue<process*,vector<process*>,process> output,
unsigned int time)
{
	cout<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<"   State of the System at the end of "<<time<<endl;
	cout<<endl;

	//print the active process if valid
	cout<<"   Active cpu process   :";
	if(cpu!=NULL)
		cout<<setw(10)<<(*cpu).ProcessName<<endl;
	else
		cout<<setw(10)<<"(NONE)"<<endl;

	cout<<"   Active input process :";
	if(in!=NULL)
		cout<<setw(10)<<(*in).ProcessName<<endl;
	else
		cout<<setw(10)<<"(NONE)"<<endl;

	cout<<"   Active output process:";
	if(out!=NULL)
		cout<<setw(10)<<(*out).ProcessName<<endl;
	else
		cout<<setw(10)<<"(NONE)"<<endl;
	cout<<endl;

	//print out the active process and the rest of the queue
	cout<<"   Entry queue processes:"<<endl<<"   ";
	if(entry.empty())
		cout<<"(EMPTY)";
	while(!entry.empty())
	{
		cout<<(*entry.front()).ProcessName<<" ";
		entry.pop();
	}
	cout<<endl<<endl;

        //print out the active process and the rest of the queue
	cout<<"   Ready queue processes:"<<endl<<"   ";
	if(cpu!=NULL)
		cout<<(*cpu).ProcessName<<" ";
	if(ready.empty() && cpu==NULL)
		cout<<"(EMPTY)";
	while(!ready.empty())
	{
		cout<<(*ready.top()).ProcessName<<" ";
		ready.pop();
	}
	cout<<endl<<endl;

        //print out the active process and the rest of the queue
	cout<<"   Input queue processes:"<<endl<<"   ";
	if(in!=NULL)
		cout<<(*in).ProcessName<<" ";
	if(input.empty() && in==NULL)
		cout<<"(EMPTY)";
	while(!input.empty())
	{
		cout<<(*input.top()).ProcessName<<" ";
		input.pop();
	}
	cout<<endl<<endl;

        //print out the active process and the rest of the queue
	cout<<"   Output queue processes:"<<endl<<"   ";
	if(out!=NULL)
		cout<<(*out).ProcessName<<" ";
	if(output.empty() && out==NULL)
		cout<<"(EMPTY)";
	while(!output.empty())
	{
		cout<<(*output.top()).ProcessName<<" ";
		output.pop();
	}

	cout<<endl<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<endl;
}

/***************************************************************
summary

Use: to print out the final infomation about the system

Parameters:	int info[]: contains all the info to print

Returns: nothing
***************************************************************/
void summary(unsigned int info[])
{
	cout<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<"                Summary"<<endl<<endl;
	cout<<"   Time taken                        : "<<setw(3)<<info[0]<<endl;
	cout<<"   Number of finished processes      : "<<setw(3)<<info[1]<<endl;
	cout<<"   Number of processes left in queues: "<<setw(3)<<info[2]<<endl;
	cout<<"   Idle time of cpu                  : "<<setw(3)<<info[3]<<endl;
	cout<<"   Idle time of intput               : "<<setw(3)<<info[4]<<endl;
	cout<<"   Idle time of output               : "<<setw(3)<<info[5]<<endl;
	cout<<"--------------------------------------------"<<endl;
}

//end of header file
#endif
