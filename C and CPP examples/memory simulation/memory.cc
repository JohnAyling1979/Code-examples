/**********************************************************************
CSCI 480 - Assignment 6 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: Nov 15, 2017

Purpose: To simulate memory management.
**********************************************************************/
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<string>
#include<list>
#include"Block.h"

#define KB 1024
#define MB 1024*1024
//back up '?' isn't found
#define MAXTIME 5000

using namespace std;

//function headers
void init(list<Block>&);
void printContent(list<Block>, list<Block>);
void load(list<Block>&, list<Block>&,char,string,int,string);
void terminate(list<Block>&, list<Block>& ,string);
void allocate(list<Block>&, list<Block>&,char,string,int,string);
void deallocate(list<Block>&, list<Block>&,string,string);
void combine(list<Block>&);
list<Block>::iterator best(list<Block>&,int);
list<Block>::iterator first(list<Block>&,int);
bool compareAddress(Block,Block);


/********************************************************************
main

Use: driver function

Parameters: 	1.  int argc: number of elements on the command line
		2.  char* argv[]: any array of char*(strings) on the
		    command line

Returns: 0 at end
********************************************************************/
int main(int argc,char* argv[])
{
	int size;
	int tic=0;
	list<Block> inUse;
	list<Block> avail;
	char fit;
	char type;
	string procID;
	string blockID;
	ifstream input;

	//check command lines
	if(argc<2)
	{
		cerr<<"Must use command line arguments B or F"<<endl;
		exit(EXIT_FAILURE);
	}
	if(argc>2)
	{
		cerr<<"Too many command arguments"<<endl;
		exit(EXIT_FAILURE);
	}

        //move command line argument to char
	//for easier reference
	fit=argv[1][0];

	//sets capital
	if(fit=='f')
		fit='F';
	if(fit=='b')
		fit='B';

	//checks for valid values
	if(fit!='F' && fit!='B')
	{
		cerr<<"Please use B or F for command line argument"<<endl;
		exit(EXIT_FAILURE);
	}

	//open data file
	input.open("data6.txt");

        //test input file
        if(!input.is_open())
        {
                cerr<<"Data file did not open"<<endl;
                exit(EXIT_FAILURE);
        }

	//initualize the memory
	init(avail);

	//report header
	cout<<"This is a memory-management simulation using ";
	if(fit=='F')
		cout<<"First-Fit";
	else
		cout<<"Best-Fit";
	cout<<endl<<endl<<endl;

	//get first char
	input>>type;

	//run until delim is found
	while(type!='?' && tic<MAXTIME)
	{
		//print content
		printContent(inUse,avail);

		//branch per type
		switch(type)
		{
			case 'L':
				input>>procID;
				input>>size;
				input>>blockID;
				load(inUse,avail,fit,procID,size,blockID);
				break;
			case 'A':
				input>>procID;
				input>>size;
				input>>blockID;
				allocate(inUse,avail,fit,procID,size,blockID);
				break;
			case 'D':
				input>>procID;
				input>>blockID;
				deallocate(inUse,avail,procID,blockID);
				break;
			case 'T':
				input>>procID;
				terminate(inUse,avail,procID);
		}

		//read next line
		input>>type;

		//increast time(backup for '?')
		tic++;
	}

	if(tic==MAXTIME)
		cout<<"Simulation has hit max time"<<endl<<endl;

	//final print
	printContent(inUse,avail);

	//close file
	input.close();

	//return
	return 0;
}

/********************************************************************
inti

Use: to set up the starting memory blocks

Parameters:	1.  list<Block>& avail: is the list of all available
		    blocks

Returns: nothing
********************************************************************/
void init(list<Block>& avail)
{
	int address;
	Block newBlock(3*MB,MB);

	//add first block 1MB
	avail.push_back(newBlock);

	//2 blocks 2MB each
	address=4*MB;
	newBlock.setSize(2*MB);
	for(int i=0;i<2;i++)
	{
		//add block
		newBlock.setAddress(address);
		avail.push_back(newBlock);

		//shift address
		address+=2*MB;
	}

	//2 blocks 4MB each
	newBlock.setSize(4*MB);
	for(int i=0;i<2;i++)
	{
		//new block pointed to by next
		newBlock.setAddress(address);
		avail.push_back(newBlock);

		//shift the address
		address+=4*MB;
	}
}

/********************************************************************
printContent

Use: to print information about the system

Parameters:	1.  list<Block> inUse: current blocks in use
		2.  list<Block> avail: current available blocks

Returns: nothing
********************************************************************/
void printContent(list<Block> inUse,list<Block> avail)
{
	int total=0;

	//OS info
	cout<<"Current Memory usage:"<<endl<<endl;
	cout<<"OS: 0-"<<3*MB-1<<endl<<endl;
	cout<<"In use:"<<endl;

	//check if empty
	if(inUse.empty())
		cout<<"None"<<endl<<endl;
	else
	{
		cout<<" PID     BLOCKID     Starting address     Size"<<endl;
		//go through list
		for(list<Block>::iterator i=inUse.begin();i!=inUse.end();i++)
		{
			cout<<(*i).getProcess()<<"        ";
			cout<<(*i).getBlock();
			cout<<setw(16)<<(*i).getAddress();
			cout<<setw(14)<<(*i).getSize()<<endl;
			total+=(*i).getSize();
		}
		cout<<endl;
	}
	cout<<"Total size of the list = "<<total<<endl<<endl;
	//reset total
	total=0;

	cout<<"Current available:"<<endl;
	if(avail.empty())
		cout<<"None"<<endl<<endl;
	else
	{
		cout<<"        Starting address          Size"<<endl;
		//go through list
		for(list<Block>::iterator i=avail.begin();i!=avail.end();i++)
        	{
			cout<<setw(19)<<(*i).getAddress();
			cout<<setw(19)<<(*i).getSize()<<endl;
			total+=(*i).getSize();
        	}
		cout<<endl;
	}
	cout<<"Total size of the list = "<<total<<endl<<endl;
}

/********************************************************************
load

Use: to load the process into a memory block

Parameters:	1.  list<Block>& InUse: the in use block list
		2.  list<Block>& Avail: the availible block list
		3.  char fit: to choose between best or first
		4.  string procID: the new process ID
		5.  int size: the size of the new process
		6.  string blockID: the block ID

Returns: nothing
********************************************************************/
void load(list<Block>& InUse,list<Block>& Avail,char fit,string procID,int size,string blockID)
{
	//create new block
	Block newBlock(0,size,procID,blockID);
	list<Block>::iterator i;

	cout<<"Transaction: Request to load process "<<procID<<", Block ID "<<blockID<<" using"<<endl;
	cout<<size<<" bytes of memory."<<endl<<endl;

	//first or best
	if(fit=='F')
		i=first(Avail,size);
	else
		i=best(Avail,size);

	//assign the memory if avail
	if(i==Avail.end())
		cerr<<"Insufficient memory space"<<endl<<endl;
	else
	{
		cout<<"Sufficient Memory Block found! Size: "<<(*i).getSize()<<endl;
		//update address on the new block
		newBlock.setAddress((*i).getAddress());

		//adjust available
		(*i).setAddress((*i).getAddress()+size);
		(*i).setSize((*i).getSize()-size);

		//if size=0 delete block
		if((*i).getSize()==0)
			Avail.erase(i);;

		//put the new block in front of the first node
		InUse.push_front(newBlock);

		//print message
		cout<<"Process "<<procID<<" has been loaded into memory"<<endl<<endl;
	}
}

/********************************************************************
allocate

Use: to allocate extra memory block to running processes

Parameters:	1.  list<Block>& InUse: list of in use memory blocks
		2.  list<Block>& Avail: list of available memory blocks
		3.  char fit: tells wether best for first fit
		4.  string procID: process id
		5.  int size: size need for new block
		6.  string blockID: block id

Returns: nothing
********************************************************************/
void allocate(list<Block>& InUse,list<Block>& Avail,char fit,string procID,int size,string blockID)
{
	//create new block
	Block newBlock(0,size,procID,blockID);
	list<Block>::iterator i=InUse.begin();

	cout<<"Transaction: Request to Allocate additional "<<size<<" bytes for process "<<procID<<","<<endl;
	cout<<"Block ID: "<<blockID<<endl;

	//check that process exist
	for(;i!=InUse.end();i++)
		if((*i).getProcess()==procID)
			break;

	if(i==InUse.end())
		cout<<"Could not load block. Process is not running"<<endl<<endl;
	else
	{
		//first or best
		if(fit=='F')
			i=first(Avail,size);
		else
			i=best(Avail,size);

		//assign the memory if avail
		if(i==Avail.end())
			cerr<<"Insufficient memory space"<<endl<<endl;
		else
		{
			cout<<"Sufficient Memory Block found! Size: "<<(*i).getSize()<<endl;
			//update the address
			newBlock.setAddress((*i).getAddress());

			//adjust available
			(*i).setAddress((*i).getAddress()+size);
			(*i).setSize((*i).getSize()-size);

			//if size=0 delete block
			if((*i).getSize()==0)
				Avail.erase(i);;

			//put the new block in front of the first node
			InUse.push_front(newBlock);

			//print message
			cout<<"Process "<<procID<<" has block "<<blockID<<" loaded into memory"<<endl<<endl;
		}
	}
}

/********************************************************************
deallocate

Use: to return memory block back to available memory

Parameters:     1.  list<Block>& InUse: list of in use memory blocks
                2.  list<Block>& Avail: list of available memory blocks
                3.  string procID: process id
                4.  string blockID: block id

Returns: nothing
********************************************************************/
void deallocate(list<Block>& inUse,list<Block>& avail,string procID,string blockID)
{
	Block newBlock;
	list<Block>::iterator i=inUse.begin();

	cout<<"Transaction: Request to DeAllocate Block ID: "<<blockID<<" for process "<<procID<<"."<<endl;

	//search for process
	for(;i!=inUse.end();i++)
		//if found break out
		if((*i).getProcess()==procID && (*i).getBlock()==blockID)
			break;

	//check if found
	if(i==inUse.end())
		cerr<<"Block "<<blockID<<" not found"<<endl<<endl;
	else
	{
		cout<<"Memory Block found!"<<endl;

		//make new block for available
		newBlock.setAddress((*i).getAddress());
		newBlock.setSize((*i).getSize());

		//remove process
		inUse.erase(i);

		//put new block to list
		avail.push_back(newBlock);

		//print message
		cout<<"Block "<<blockID<<" has been deleted"<<endl;

		//sort list by starting address
		avail.sort(compareAddress);

		//combine blocks
		combine(avail);
	}
}

/********************************************************************
terminate

Use: to remove process from the memory

Parameters:     1.  list<Block>& InUse: list of in use memory blocks
                2.  list<Block>& Avail: list of available memory blocks
                3.  string procID: process id

Returns: nothing
********************************************************************/
void terminate(list<Block>& inUse,list<Block>& avail,string procID)
{
	Block newBlock;
	bool notFound=true;
	list<Block>::iterator i=inUse.begin();

	cout<<"Transaction: Request to Terminate process "<<procID<<endl;

	//search for process
	while(i!=inUse.end())
	{
		//if found push pointer onto list
		if((*i).getProcess()==procID)
		{
			//update found flag
			notFound=false;

			//make new block for available
			newBlock.setAddress((*i).getAddress());
			newBlock.setSize((*i).getSize());

			//remove process
			i=inUse.erase(i);

			//put new block to list
			avail.push_back(newBlock);
		}else
			i++;
	}

	//check if found
	if(notFound)
		cerr<<"Process not found"<<endl<<endl;
	else
	{
		//print message
		cout<<"Process "<<procID<<" has been deleted"<<endl;

		//sort list by starting address
		avail.sort(compareAddress);

		//combine blocks
		combine(avail);
	}
}

/********************************************************************
combine

Use: to to combine contiguos memory blocks

Parameters:     1.  list<Block>& myList: list of memory blocks to compact

Returns: nothing
********************************************************************/
void combine(list<Block>& myList)
{
	list<Block>::iterator next=myList.begin();
	list<Block>::iterator curr=next++;
	//at this point curr=begining and next=next object

	//go through the available list
	while(next!=myList.end())
	{
		//while the memory is contiguos and less then 4MB
		while((*curr).getAddress()+(*curr).getSize()==(*next).getAddress() && (*curr).getSize()+(*next).getSize()<=4*MB)
		{
			//display message,update size and delete merged block
			cout<<"Merging free memory block at address "<<(*curr).getAddress()<<" with free memory block at address "<<(*next).getAddress()<<endl;
			(*curr).setSize((*curr).getSize()+(*next).getSize());
			next=myList.erase(next);

			//if the next points to end break out of inner while
			if(next==myList.end())
				break;
		}
		//move both pointers to next block
		next=++curr;

		//as long as next location was not end increase next to next block
		if(next!=myList.end())
			next++;
	}
	//spacing
	cout<<endl;
}

/********************************************************************
best

Use: Algorithm for best fist

Parameters:	1.  list<Block> Avail: list of available blocks
			2.  int size: Size of the new block to make

Returns: list<Block>::iterator which will point to a block if found
or end of list if blocks large enough
********************************************************************/
list<Block>::iterator best(list<Block>& Avail,int size)
{
	list<Block>::iterator i=Avail.begin();
	list<Block>::iterator best=Avail.end();

	//search till end of list
	for(;i!=Avail.end();i++)
	{
		//if process will fit break out
		if((*i).getSize()>=size)
		{
			//check if starting value
			if(best==Avail.end())
				best=i;
			//or check if new size is less then the current best size
			else if((*i).getSize()<(*best).getSize())
				best=i;
		}
	}

	//return best.  will be end if it doesn't fit
	return best;
}

/********************************************************************
first

Use: Algorithm for first fist

Parameters:	1.  list<Block> Avail: list of available blocks
			2.  int size: Size of the new block to make

Returns: list<Block>::iterator which will point to a block if found
or end of list if blocks large enough
********************************************************************/
list<Block>::iterator first(list<Block>& Avail,int size)
{
	list<Block>::iterator i=Avail.begin();

	//search till end of list
	for(;i!=Avail.end();i++)
		//if process will fit break out
		if((*i).getSize()>=size)
			break;

	//returns iterator. Will be end if it doesn't fit
	return i;
}

/********************************************************************
compareAddress

Use: used to sort the blocks by addrss

Parameters:	1.  Block first: first block to check
		2.  Block second: the second block to check

Returns: bool(true when the first is lower
********************************************************************/
bool compareAddress(Block first,Block second)
{
        if(first.getAddress()<second.getAddress())
                return true;
        else
                return false;
}
