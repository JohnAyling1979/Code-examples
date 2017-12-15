/***********************************************************
CSCI 480 - Assignment 4 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: October 13, 2017

Purpose: To simulate process activity in a priority driven OS
************************************************************/
#include"priority.h"

int main()
{
	queue<process*> Entry; //starting queue FCFS
  	priority_queue<process*,vector<process*>,process> Ready,Input,Output; //priority queue higher number higher priority

	//active process of each queue
	process* Active=NULL;
	process* IActive=NULL;
	process* OActive=NULL;

	unsigned int pCount=0; //count of current active processes
	unsigned int Timer=0; //system timer
	unsigned int finished=0; //number of finished processes
	unsigned int info[6]; //info to pass to the summary function
	unsigned int CPUidle=0; //CPU idle counter
	unsigned int Iidle=0; //Input idle counter
	unsigned int Oidle=0; //Output idle counter

	//load the processes into memory
	loadProcesses(Entry);

	//start main loop
	while(Timer<MAX_TIME && (!Entry.empty() || !Ready.empty() || !Input.empty() || !Output.empty() || Active!=NULL || IActive!=NULL || OActive!=NULL))
	{
		//if count is less the the max and entry is not empty
		//fill with available processes
		if(pCount<AT_ONCE && !Entry.empty())
			pCount=fillReady(Entry,Ready,pCount,Timer);

		//Assign active processes for the current tick
		setActive(Active,IActive,OActive,Ready,Input,Output,Timer);

		//for CPU burst
		if(Active!=NULL)
			pCount=cpuBurst(Active,Ready,Input,Output,finished,Timer,pCount);
		else
			CPUidle++;
		//for Input burst
		if(IActive!=NULL)
			ioBurst(IActive,Ready,Timer,1);
		else
			Iidle++;

		//for Output burst
		if(OActive!=NULL)
			ioBurst(OActive,Ready,Timer,0);
		else
			Oidle++;

		//display system state at the end of tick based of
		//how often
		if(Timer%HOW_OFTEN==0)
			statUpdate(Active,IActive,OActive,Entry,Ready,Input,Output,Timer);

		Timer++;
	}

	//load info for summary
	info[0]=Timer;
	info[1]=finished;
	info[2]=Entry.size()+Ready.size()+Input.size()+Output.size();
	//CPU idle is 0 for this sample data because ready queue was never empty
	//so CPU ran every tick
	info[3]=CPUidle;
	info[4]=Iidle;
	info[5]=Oidle;
	summary(info);

	return 0;
}
