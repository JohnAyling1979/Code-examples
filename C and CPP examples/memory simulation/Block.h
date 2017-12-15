#ifndef BLOCK
#define BLOCK

#include<string>

/********************************************************************
Block class

	data members:
		address-starting address of the memory block
		size-size of the memory block
		processID-process ID
		blockID-block ID

	member functions:
                Block ()-default constructor
                Block (int,int)-constructor to assign address and size
                Block (int,int,std::string,std::string)-constructor to
			assign all data members
                void setAddress(int)-used to set the address
                void setSize(int)-used to set the size
                void setProcess(std::string)-used to set the process
                void setBlock(std::string)-used to set the block
                int getAddress()-used to get the current address
                int getSize()-used to get the current size
                std::string getProcess()-used to get the current 
			process id
                std::string getBlock()-used to get the current block id

********************************************************************/
class Block
{
	private:
		int address;
		int size;
        	std::string processID;
		std::string blockID;
	public:
		Block ();
		Block (int,int);
		Block (int,int,std::string,std::string);
		void setAddress(int);
		void setSize(int);
		void setProcess(std::string);
		void setBlock(std::string);
                int getAddress();
                int getSize();
                std::string getProcess();
                std::string getBlock();
};

#endif
