//Start of header
#ifndef PROCESS
#define PROCESS

#include<string>
#include<utility>

//process structure which holds all the commponents
//given by the assignment plus the comparison function
class process
{
	public:
		std::string ProcessName;
		unsigned int Priority;
		unsigned int ProcessID;
		static unsigned int ProcessID_counter;
		unsigned int ArrivalTime;
		std::pair<char,unsigned int> History[12];
		unsigned int Sub;
		unsigned int CPUTimer;
		unsigned int IOTimer;
		unsigned int CPUTotal;
		unsigned int ITotal;
		unsigned int OTotal;
		unsigned int CPUCount;
		unsigned int ICount;
		unsigned int OCount;
		unsigned int ReadyStart;

		process();
		bool operator()(process*,process*);
};

//sets starting process ID
unsigned int process::ProcessID_counter=PROCESS_NUMBER;

/***************************************************************
constructor

Use: to assign default values to process

Parameters:	None

Returns: None
***************************************************************/
process::process()
{
	ProcessID=ProcessID_counter++;
	Sub=0;
	CPUTotal=0;
	ITotal=0;
	OTotal=0;
	CPUCount=0;
	ICount=0;
	OCount=0;
	ReadyStart=0;
}

/***************************************************************
()

Use: override the () operator to be used in the priority queue sort

Parameters:     process* oldP: first process to compare
		process* newP: second process to compare

Returns: bool:	true when the new priority > then old or if
		priority is = will be true if the start time was
		smaller
***************************************************************/
bool  process::operator()(process* oldP,process* newP)
{
	if((*oldP).Priority == (*newP).Priority)
		return (*oldP).ReadyStart > (*newP).ReadyStart;

	return (*oldP).Priority < (*newP).Priority;
}

//end of header
#endif
