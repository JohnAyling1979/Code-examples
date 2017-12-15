#include"Block.h"


/********************************************************************
Block()

Use: used to set the default value when an objeck is created

Parameters: 1.  void* threadid: the id number used in the
		create thread function

Returns: nothing
********************************************************************/
Block::Block()
{
        address=0;
        size=0;
        processID="";
        blockID="";
}

/********************************************************************
Block(int,int)

Use: used to set the default value when an objeck is created

Parameters:	1.  int a: value for the address
		2.  int s: value for the size

Returns: nothing
********************************************************************/
Block::Block(int a,int s)
{
	address=a;
	size=s;
	processID="";
	blockID="";
}

/********************************************************************
Block(int,int,string,string)

Use: used to set the default value when an objeck is created

Parameters:	1.  int a: value for the address
		2.  int s: value for the size
		3.  string pID: process ID
		4.  string bID: block ID

Returns: nothing
********************************************************************/
Block::Block(int a,int s,std::string pID,std::string bID)
{
        address=a;
        size=s;
        processID=pID;
        blockID=bID;
}

/********************************************************************
setAddress

Use: to set just the address

Parameters: 1.  int a: new address value

Returns: nothing
********************************************************************/
void Block::setAddress(int a)
{
	address=a;
}

/********************************************************************
setSize

Use: used to set the size

Parameters: 1.  int s: value of the size

Returns: nothing
********************************************************************/
void Block::setSize(int s)
{
	size=s;
}

/********************************************************************
setProcess

Use: used to set the process ID

Parameters: 1.  string id: new process ID

Returns: nothing
********************************************************************/
void Block::setProcess(std::string id)
{
	processID=id;
}

/********************************************************************
setBlock

Use: used to set the block id

Parameters: 1.  string id: new block id

Returns: nothing
********************************************************************/
void Block::setBlock(std::string id)
{
	blockID=id;
}

/********************************************************************
getAddress

Use: used to get the current address

Parameters: none

Returns: the blocks address
********************************************************************/
int Block::getAddress()
{
	return address;
}

/********************************************************************
getSize

Use: used to get the current size

Parameters: none

Returns: the blocks size
********************************************************************/
int Block::getSize()
{
	return size;
}

/********************************************************************
getProcess

Use: used to get the process ID

Parameters: none

Returns: the process id
********************************************************************/
std::string Block::getProcess()
{
	return processID;
}

/********************************************************************
getBlock

Use: used to get the block id

Parameters: none

Returns: the block id
********************************************************************/
std::string Block::getBlock()
{
	return blockID;
}

