/**********************************************************************
Entry

This class is used to create file entries in the directory

member variables:
	std::string fileName: name of the file
	int size": number of bytes in the the file
	int blockNumber: first memory block assigned to the file

member functions:
	Entry(std::string,int,int): used to initulize the entry
	std::string getName(): used to retreive the file name
	int getSize(): used to retreive the size
	int getBlock(): used to retreive the first block
	void setName(std::string): used to update the file name
	void setSize(int): used to update the size
	void setBlock(int): used to update the first block

**********************************************************************/
#ifndef ENTRY
#define ENTRY

#include<string>

class Entry
{
	private:
		std::string fileName;
		int size;
		int blockNumber;

	public:
		Entry(std::string,int,int);
		std::string getName();
		int getSize();
		int getBlock();
		void setName(std::string);
		void setSize(int);
		void setBlock(int);
};

#endif
