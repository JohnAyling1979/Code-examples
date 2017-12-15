#include"entry.h"

/********************************************************************
Entry::Entry

Use: constructor to initulize members

Parameters:     1.  std::string inName: is the file name
                2.  int inSize: is the size of the file
                3.  int inBlock: is the number of the first memory block

Returns: nothing
********************************************************************/
Entry::Entry(std::string inName,int inSize,int inBlock)
{
	fileName=inName;
	size=inSize;
	blockNumber=inBlock;
}

/********************************************************************
Entry::getName

Use: to get the file name

Parameters:     None

Returns: std::string: The file name
********************************************************************/
std::string Entry::getName()
{
	return fileName;
}

/********************************************************************
Entry::getSize

Use: to get the file size

Parameters:     None

Returns: int: The file size
********************************************************************/
int Entry::getSize()
{
	return size;
}

/********************************************************************
Entry::getBlock

Use: to get the first memory block

Parameters:     None

Returns: int: The # of the first block
********************************************************************/
int Entry::getBlock()
{
	return blockNumber;
}

/********************************************************************
Entry::setName

Use: to set/update the file name

Parameters:     std::string: The new file name

Returns: None
********************************************************************/
void Entry::setName(std::string newName)
{
	fileName=newName;
}

/********************************************************************
Entry::setSize

Use: to set/update the file size

Parameters:     int: The new file size

Returns: None
********************************************************************/
void Entry::setSize(int newSize)
{
	size=newSize;
}

/********************************************************************
Entry::setBlock

Use: to set/update the block size

Parameters:     int: The new block size

Returns: None
********************************************************************/
void Entry::setBlock(int newBlock)
{
	blockNumber=newBlock;
}
