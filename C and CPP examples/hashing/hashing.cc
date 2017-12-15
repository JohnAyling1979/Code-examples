/***********************************************************
CSCI 340 - Assignment 8 - Spring 2017

Progammer:	John Ayling
Z-ID:		z981329
Section:	3
TA:		Khaja Anwar Ali Siddiqui
Date Due:	Apr. 20 11:59 pm

Purpose: To create, search, print, and manage a hash table
************************************************************/
//needed includes
#include <fstream>
#include <iostream>
#include <iomanip>
#include"hash.h"

using namespace std;

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key)
{
   return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
}

/***************************************************************
HT::HT(constructor)
Use:		To create a new hash structure
Parameters:	1. int s: The size of the new heap table which
		has a default value of 11
Returns:	None
***************************************************************/
HT::HT(int s=11)
{
	//Allocate the memory for the table and save the pointer
	hTable=new vector<Entry>(s);

	//Set the table and item variables
	table_size=s;
	item_count=0;
}

/***************************************************************
HT::~HT(destructor)
Use:		To free the memory that was set at the creation
		of the object
Parameters:	none
Returns:	None
***************************************************************/
HT::~HT()
{
	//Deallocate the memory
	delete(hTable);
}

/***************************************************************
HT::search
Use:		Hash the key and then from that spot search the
		table for the key.
Parameters:	1. string& key: The key which is being searched
		for
Returns:	int: The locaton of the entry if found or -1
***************************************************************/
int HT::search(const string& key)
{
	//Get the table location
	int loc=hashing(key);

	//search starting at the hash location and go until you find
	//the first unused spot or if the table is full have search
	//the hole table
	while(hTable->at(loc%table_size).key!="---" && loc<hashing(key)+table_size)
	{
		//if keys match return the location
		if(hTable->at(loc%table_size).key==key)
			return loc%table_size;
		//move to next location
		loc++;
	}

	//Not found so return -1
	return -1;
}

/********************************************************************
HT::insert
Use:		To insert an entry into the hash table
Parameters:	1. Entry& e: The entry that need to be inserted
Returns:	bool: True if the entry was inserted.
		      False if there was an error with the insertion
********************************************************************/
bool HT::insert(const Entry& e)
{
        //Checks if the table is full
        if(table_size==item_count)
	{
                cout<<"Can not insert entry. Table is full"<<endl;
		return false;
	}

	//Checks if the key is already in the table
	if(search(e.key)!=-1)
	{
		cout<<"Entry "<<e.key<<" allready exists"<<endl;
		return false;
	}

	//gets the location in the table
	int loc=hashing(e.key);

	//goes thru the table starting at the location looking for
	//the first empty spot
	while(hTable->at(loc).key!="---" && hTable->at(loc).key!="+++")
		loc=(loc+1)%table_size;

	//put the information into the table
	hTable->at(loc).key=e.key;
	hTable->at(loc).description=e.description;

	//increase the count and return true
	item_count++;
	return true;
}

/********************************************************************
remove
Use:		To remove an entry from the hash table
Parameters:	1. string& s: The key of the entry that needs to be
		removed
Returns:	bool: True if the entry was removed.
		      False if the entry was not in the table
********************************************************************/
bool HT::remove(const string& s)
{
	//search for the location
	int loc=search(s);

	//if it wasn't found return false
	if(loc==-1)
		return false;
	else
	{
		//set the found location empty 
		hTable->at(loc).key="+++";
		hTable->at(loc).description="";

		//lower item count and return true
		item_count--;
		return true;
	}
}

/********************************************************************
print
Use:		To print the hash table
Parameters:	None
Returns:	None
********************************************************************/
void HT::print()
{
	//prints header
	cout<<endl<<"----Hash Table-----"<<endl;

	//goes thru the table prints any non empty locations
	for(vector<Entry>::iterator i=hTable->begin();i!=hTable->end();i++)
		if(i->key!="---" && i->key!="+++")
			cout<<setw(2)<<i-hTable->begin()<<": "<<i->key<<" "<<i->description<<endl;

	//prints footer
	cout<<"-------------------"<<endl<<endl;
}

/********************************************************************
get_key
Use:		To extract the key from the input line
Parameters:	1. string& line: The string from input
Returns:	string: The 3 letter key
********************************************************************/
string get_key(const string& line)
{
	//return the substring that is the key
	return line.substr(2,3);
}

/********************************************************************
get_entry
Use:		To create the entry from the input line
Parameters:	1. string& line: The string from the input
Returns:	Entry*: a pointer to the newly created entry
********************************************************************/
Entry* get_entry(const string& line)
{
	//pointer to a new entry to return
	Entry *current=new Entry;

	//load key and description
	current->key=get_key(line);
	current->description=line.substr(6,string::npos);

	//return the pointer
	return current;
}

int main(int argc, char** argv ) {
    if ( argc < 2 ) {
        cerr << "argument: file-name\n";
        return 1;
    }

    HT ht;
    ifstream infile(argv[1], ios::in);
    string line;
    infile >> line;
    while ( !infile.eof() ) {
        if ( line[0] == 'A' ) {
            Entry* e = get_entry( line );
            ht.insert( *e );
            delete e;
        }
        else {
            string key = get_key(line);
            if ( line[0] == 'D' ) {
                cout << "Removing " << key << "...\n";
                bool removed = ht.remove( key );
                if ( removed )
                    cout << key << " is removed successfully...\n\n";
                else
                    cout << key << " does not exist, no key is removed...\n\n";
            }
            else if ( line[0] == 'S' ) {
                int found = ht.search( key );
                if ( found < 0 )
                    cout << key << " does not exit in the hash table ..." << endl << endl;
                else
                   cout << key << " is found at table position " << found << endl << endl;
            }
            else if ( line[0] == 'P' ) {
                cout << "\nDisplaying the table: " << endl;
                ht.print();
            }
            else
                cerr << "wrong input: " << line << endl;
        }
        infile >> line;
    }

    infile.close();
    return 0;
}
