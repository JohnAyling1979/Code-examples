/**********************************************************************
CSCI 480 - Assignment 7 - Fall 2017

Progammer: John Ayling
Z-ID: z981329
Section: 2
TA: David Williams/Eric Lavin
Date Due: Dec 5, 2017

Purpose: To simulate fat 12 allocation.
**********************************************************************/
#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include"entry.h"

#define SIZE 512
#define HOWOFTEN 6
#define MAXENTRY 12
#define MAXFAT 240
#define FATSIZE 4096

using namespace std;

void init(vector<short int>&,vector<Entry*>&);
void createNewFile(string,int,vector<short int>&,vector<Entry*>&);
void deleteFile(string,vector<short int>&,vector<Entry*>&);
void renameFile(string,string,vector<Entry*>&);
void copyFile(string,string,vector<short int>&,vector<Entry*>&);
void modifyFile(string,int,vector<short int>&,vector<Entry*>&,int);
void cleanup(vector<Entry*>);
void printInfo(vector<short int>,vector<Entry*>,int);
void increaseDir(vector<short int>&,vector<Entry*>&);
void decreaseDir(vector<short int>&,vector<Entry*>&);
int getEmptyBlock(vector<short int>);
vector<Entry*>::iterator fileSearch(vector<Entry*>&,string);
void defrag(vector<short int>&,vector<Entry*>&);

/********************************************************************
main

Use: driver function. Reads from a file and process the info

Parameters:     None

Returns: 0 at end
********************************************************************/
int main()
{
	vector<Entry*> dir;
	char type;
	int fileSize;
	int time=0;
	string oldFileName;
	string newFileName;
	ifstream input;
	vector<short int> fat;

	//open input file and verify it opened
	input.open("data7.txt");
	if(!input.is_open())
	{
		cerr<<"file data7.txt faile to open"<<endl;
		exit(EXIT_FAILURE);
	}

	//initulize fat and directory
	init(fat,dir);

	//print info at the start
	printInfo(fat,dir,time);

	//read first transaction
	input>>type;

	while(type!='?')
	{
		//process transaction
		switch(type)
		{
			case 'C':
				input>>oldFileName;
				input>>newFileName;
				copyFile(oldFileName,newFileName,fat,dir);
				break;
			case 'D':
				input>>oldFileName;
				deleteFile(oldFileName,fat,dir);
				break;
			case 'N':
				input>>newFileName;
				input>>fileSize;
				createNewFile(newFileName,fileSize,fat,dir);
				break;
			case 'M':
				input>>oldFileName;
				input>>fileSize;
				modifyFile(oldFileName,fileSize,fat,dir,time);
				break;
			case 'R':
				input>>oldFileName;
				input>>newFileName;
				renameFile(oldFileName,newFileName,dir);
		}

		//get next transaction
		input>>type;

		//increase time and print info if time
		if(++time%HOWOFTEN==0)
			printInfo(fat,dir,time);
	}

	//close file
	input.close();

	//print end info
	printInfo(fat,dir,time);

	//defrag the volume
//	defrag(fat,dir);

	//contiguos volume
//	printInfo(fat,dir,0);

	//clean up memory
	cleanup(dir);

	return 0;
}

/********************************************************************
printInfo

Use: to print out the contents of the directory and fat

Parameters:     1.  vector<short int> fat: is the fat table
                2.  vector<Entry*> dir: contains the list of files

Returns: nothing
********************************************************************/
void printInfo(vector<short int> fat,vector<Entry*> dir,int time)
{
	int block;
	int totalSize=0;

	cout<<"Directory and FAT information at tic "<<time<<endl<<endl;

	//directory info
	cout<<"Directory:"<<endl;
	for(vector<Entry*>::iterator i=dir.begin();i!=dir.end();i++)
	{
		cout<<"Name:  "<<(*(*i)).getName()<<"      Size:  "<<(*(*i)).getSize()<<"   "<<endl;
		cout<<"Blocks:"<<endl;
		block=(*(*i)).getBlock();
		if(block==-1)
			cout<<"NONE"<<endl<<endl;
		else
		{
			cout<<block<<" ";
			while(fat.at(block)!=-1)
			{
				block=fat.at(block);
				cout<<block<<" ";
			}
			cout<<endl<<endl;
		}

		//get totals
		totalSize+=(*(*i)).getSize();
	}

	//print out totals
	cout<<"Directory contains "<<dir.size()<<" files for a total of "<<totalSize<<" bytes"<<endl<<endl;

	//fat info
	cout<<"FAT info"<<endl;

	//print out fat
	for(int i=0;i<MAXFAT;i++)
	{
		//12 per line
		if(i%12==0)
			cout<<endl;
		cout<<setw(5)<<fat.at(i);
	}

	//spacing
	cout<<endl<<endl<<endl;
}

/********************************************************************
inti

Use: to set the fat table and starting entries

Parameters:     1.  vector<short int>& fat: is the fat table
		2.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void init(vector<short int>& fat,vector<Entry*>& dir)
{
	//allocate fat table
	fat.resize(FATSIZE);

	//enter first 2 entries
	createNewFile(".",SIZE,fat,dir);
	createNewFile("..",0,fat,dir);
}

/********************************************************************
createNewFile

Use: to add a new file to the disk

Parameters:	1.  string inName: Name of the new file
		2.  int inSize: Size of the new file
		3.  vector<short int>& fat: is the fat table
                4.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void createNewFile(string inName,int inSize,vector<short int>& fat,vector<Entry*>& dir)
{
	int loc;
	int next;
	vector<Entry*>::iterator name;

	//search if name already exits
	name=fileSearch(dir,inName);

	//if it was not at the end a file was found
	if(name!=dir.end())
	{
		cerr<<"ERROR: Can not create file. File "<<inName<<" already exists"<<endl<<endl;
	}
	else
	{
		//if directory is at max
		//assign a block before adding file
		//add a -2 if not counting the . and .. entries
		if(dir.size()%MAXENTRY==0 && dir.size()!=0)
			increaseDir(fat,dir);

		//if the size in invalid set stating block to -1
		if(inSize==0)
			dir.push_back(new Entry(inName,inSize,-1));
		else
		{
			//get first empty block
			loc=getEmptyBlock(fat);

			//add file to directory and
			//assign first block
			dir.push_back(new Entry(inName,inSize,loc));
			fat.at(loc)=-1;

			//set remaining size
			inSize-=SIZE;

			//assign addition blocks as needed
			while(inSize>0)
			{
				//find first empty empty block
				next=getEmptyBlock(fat);

				//update table with next block
				fat.at(loc)=next;

				//set next block to -1
				fat.at(next)=-1;

				//update location
				loc=next;

				//set remaining size
				inSize-=SIZE;
			}
		}
	}
}

/********************************************************************
deleteFile

Use: to remove a file to the disk

Parameters:     1.  string inName: Name of the new file
                2.  vector<short int>& fat: is the fat table
                3.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void deleteFile(string inName,vector<short int>& fat,vector<Entry*>& dir)
{
	int curr,next;
	vector<Entry*>::iterator name;

	//search for file name
	name=fileSearch(dir,inName);

	//if we made it to the end of the list file name was not found
	if(name==dir.end())
	{
		cout<<"ERROR: Can not delete file. File "<<inName<<" not found"<<endl<<endl;
	}
	else
	{
		//get starting block
		curr=(*(*name)).getBlock();

		//if it is a valid block
		//update FAT
		if(curr!=-1)
		{
			//get next block
			next=fat.at(curr);

			//deallocate current block
			fat.at(curr)=0;

			//deallocate unitl end
			while(next!=-1)
			{
				//update current
				curr=next;

				//get next block
				next=fat.at(curr);

				//deallocate current block
				fat.at(curr)=0;
			}
		}

		//delalocate the storage and remove file name from vector
		delete(*name);
		dir.erase(name);

		//check if removeing the file dropped a block
		if(dir.size()%MAXENTRY==0)
			decreaseDir(fat,dir);
	}
}

/********************************************************************
renameFile

Use: to change the name of a file

Parameters:     1.  string oldFileName: old name of the file
                2.  string newFileName: new name of the file
                3.  vector<short int>& fat: is the fat table
                4.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void renameFile(string oldFileName,string newFileName,vector<Entry*>& dir)
{
	vector<Entry*>::iterator oName=dir.begin();
	vector<Entry*>::iterator nName=dir.begin();

	//search for old name
	oName=fileSearch(dir,oldFileName);

	//search for new name
	nName=fileSearch(dir,newFileName);

	//as long as old file is found and new file is not
	//rename the file
	if(oName==dir.end())
	{
		cerr<<"ERROR: Can not rename file. File "<<oldFileName<<" does not exist."<<endl<<endl;
	}
	else if(nName!=dir.end())
	{
		cerr<<"ERROR: Can not rename file. File "<<newFileName<<" already exists"<<endl<<endl;
	}else
		(*(*oName)).setName(newFileName);
}

/********************************************************************
copyFile

Use: to make a copy of a file

Parameters:     1.  string oldFileName: old name of the file
                2.  string newFileName: new name of the file
                3.  vector<short int>& fat: is the fat table
                4.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void copyFile(string oldFileName,string newFileName,vector<short int>& fat,vector<Entry*>& dir)
{
	vector<Entry*>::iterator oName=dir.begin();
	vector<Entry*>::iterator nName=dir.begin();

	//search for old name
	oName=fileSearch(dir,oldFileName);

	//search for new name
	nName=fileSearch(dir,newFileName);

	//as long as old file is found and new file is not
	//create the copy;
	if(oName==dir.end())
	{
		cerr<<"ERROR: Can not copy file. File "<<oldFileName<<" does not exist."<<endl<<endl;
	}
	else if(nName!=dir.end())
	{
		cerr<<"ERROR: Can not copy file. File "<<newFileName<<" already exists."<<endl<<endl;
	}else
		createNewFile(newFileName,(*(*oName)).getSize(),fat,dir);
}

/********************************************************************
modifyFile

Use: to change the size of a file

It was done this way per the assignment. Personally I would of updated
size and then updated the blocks assigned to it

Parameters:     1.  string oldFileName: old name of the file
                2.  int newSize: new size to allocate
                3.  vector<short int>& fat: is the fat table
                4.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void modifyFile(string oldFileName,int newSize,vector<short int>& fat,vector<Entry*>& dir,int time)
{
	stringstream ss;
	string tempFile;
	vector<Entry*>::iterator oName=dir.begin();

	//search for old name
	oName=fileSearch(dir,oldFileName);

	if(oName==dir.end())
	{
		cerr<<"ERROR: Can not modify file. File "<<oldFileName<<" does not exist."<<endl<<endl;
	}else
	{
		//create tempfilename
		ss<<oldFileName<<time;
		tempFile=ss.str();

		//allocate blocks for temp file
		createNewFile(tempFile,newSize,fat,dir);

		//delete original file
		deleteFile(oldFileName,fat,dir);

		//rename tempfile to original
		renameFile(tempFile,oldFileName,dir);
	}
}

/********************************************************************
cleanup

Use: to deallocate all pointers

Parameters:     1.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void cleanup(vector<Entry*> dir)
{
        for(vector<Entry*>::iterator i=dir.begin();i!=dir.end();i++)
        {
                delete (*i);
        }
}

/********************************************************************
fileSearch

Use: to search the directory for a file name

Parameters:     1.  vector<Entry*>& dir: contains the list of files
		2.  string name: Name of the file we are looking for

Returns: nothing
********************************************************************/
vector<Entry*>::iterator fileSearch(vector<Entry*>& dir,string name)
{
	vector<Entry*>::iterator loc=dir.begin();

	//search for name
	for(;loc!=dir.end();loc++)
		if((*(*loc)).getName()==name)
			break;

	//return iterator
	return loc;
}

/********************************************************************
increaseDir

Use: to assign additional block to the directory

Parameters:     1.  vector<short int>& fat: is the fat table
                2.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void increaseDir(vector<short int>& fat,vector<Entry*>& dir)
{
	int next=0,loc=0;
	vector<Entry*>::iterator dirName=dir.begin();

	//find the last block
	while(fat.at(loc)!=-1)
		loc=fat.at(loc);

	//find the first empty block
	next=getEmptyBlock(fat);

	//assign new block
	//and increase size
	fat.at(loc)=next;
	fat.at(next)=-1;
	(*(*dirName)).setSize((*(*dirName)).getSize()+SIZE);
}

/********************************************************************
decreaseDir

Use: to deallocate a block assigned to the dir

Parameters:     1.  vector<short int>& fat: is the fat table
                2.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void decreaseDir(vector<short int>& fat,vector<Entry*>& dir)
{
	int curr=0,next=0;
	vector<Entry*>::iterator dirName=dir.begin();


	//get next block
	//we know it has at least two blocks
	next=fat.at(curr);

	//look for last block
	while(fat.at(next)!=-1)
	{
		//save current
		curr=next;
		//get next
		next=fat.at(next);
	}

	//free last block
	fat.at(next)=0;

	//set second to last block as end
	//and decrease size
	fat.at(curr)=-1;
	(*(*dirName)).setSize((*(*dirName)).getSize()-SIZE);
}

/********************************************************************
getEmptyBlock

Use: to get the next empty block

Parameters:     1.  vector<short int>& fat: is the fat table

Returns: unsigned int which is the locatiom of an empty block
********************************************************************/
int getEmptyBlock(vector<short int> fat)
{
	int loc=0;

	//find first empty empty block for the file
	for(;loc!=FATSIZE;loc++)
		if(fat.at(loc)==0)
			break;

	//if no empty blocks exit with error
	if(loc==FATSIZE)
	{
		cerr<<"Out off space"<<endl;
		exit(EXIT_FAILURE);
	}

	return loc;
}

/********************************************************************
defrag

Use: to rewrite the files into contiguous strorage

Parameters:     1.  vector<short int>& fat: is the fat table
                2.  vector<Entry*>& dir: contains the list of files

Returns: nothing
********************************************************************/
void defrag(vector<short int>& fat,vector<Entry*>& dir)
{
	//rewrite to end of volume
	vector<Entry*>::iterator fileName=dir.begin();
	int block,pre;
	int end=FATSIZE;

	cout<<"Defraging volume:  ";

	while(fileName!=dir.end())
	{
		//get first block
		block=(*(*fileName)).getBlock();
		if(block!=-1)
		{
			//find an empty
			while(fat.at(--end)!=0);


			//move to endblock
			fat.at(end)=fat.at(block);
			fat.at(block)=0;
			cout<<".";

			//update dir
			(*(*fileName)).setBlock(end);


			//move any remaining blocks
			while(fat.at(end)!=-1)
			{
				//go to next block
				block=fat.at(end);

				//save previouse
				pre=end;

				//find an empty
				while(fat.at(--end)!=0);

				//move info to the end
				fat.at(end)=fat.at(block);
				fat.at(block)=0;
				cout<<".";

				//update link
				fat.at(pre)=end;
			}
		}
		//next file
		fileName++;
	}

	//place back
	fileName=dir.begin();
	end=-1;

	while(fileName!=dir.end())
	{
		//get first block
		block=(*(*fileName)).getBlock();
		if(block!=-1)
		{
			//find an empty
			while(fat.at(++end)!=0);


			//move to front
			fat.at(end)=fat.at(block);
			fat.at(block)=0;
			cout<<".";

			//update dir
			(*(*fileName)).setBlock(end);


			//move any remaining blocks
			while(fat.at(end)!=-1)
			{
				//go to next block
				block=fat.at(end);

				//save previouse
				pre=end;

				//find an empty
				while(fat.at(++end)!=0);

				//move info to the front
				fat.at(end)=fat.at(block);
				fat.at(block)=0;
				cout<<".";

				//update link
				fat.at(pre)=end;
			}
		}
		//next file
		fileName++;
	}
	cout<<endl<<endl;
}
