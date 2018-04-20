/***********************************************************
CSCI 340 - Assignment 2 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Feb. 10 11:59 pm

Purpose: This program show the use of multiple routines from
<algorithm>
************************************************************/

//Addes all includes nessesary to run the program
#include<iomanip>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<algorithm>

//std name usage for input/output
using namespace std;

const int DATA_SIZE = 200;
const int SEARCH_SIZE = 100;
const int DATA_SEED = 7;
const int SEARCH_SEED = 9;

//added consts per the assignment
const int LOW = 1;
const int HIGH = 200;
const int NO_ITEMS = 12;
const int ITEM_W = 5;

/***************************************************************
genRndNums
Use: Fill a vector with random numbers based of a seed value using
     the member function size to find the end
Parameters: 1. v:  vector to be filled with random numbers
            2. seed: value used to generate the random numbers
Returns: void
***************************************************************/
void genRndNums( vector<int>& v, int seed )
{
	//sets the seed
	srand(seed);

	for(unsigned int x=0;x!=v.size();x++)
		v.at(x)=rand()%HIGH+LOW;
}

/***************************************************************
linearSearch
Use: search thru the vector for a certain element using the find
     algorithm
Parameters: 1. inputVec:  Contains the address of the vector
            2. x:  The number which is being searched for
Returns: int(the direct access location of the value or -1 if not found)
***************************************************************/
int linearSearch( const vector<int>& inputVec, int x)
{
	//uses find from <algorithm> and sets it to place
	vector<int>::const_iterator place=find(inputVec.begin(),inputVec.end(),x);

	//if place == the value return the location
	if(*place==x)
		return place-inputVec.begin();

	//else returns -1
	else
		return -1;
}

/***************************************************************
binarySearch
Use: binary search thru the vector for a certain element using
     equal_range from algorithm
Parameters: 1. inputVec:  Contains the address of the vector
            2. x:  The number which is being searched for
Returns: int(the direct access location of the value or -1 if not found)
***************************************************************/
int binarySearch( const vector<int>& inputVec, int x)
{
	//create a pair object for use with equal_range
	pair<vector<int>::const_iterator,vector<int>::const_iterator> range;

	//perform a binary search for x on the full vectory
	range=equal_range(inputVec.begin(),inputVec.end(),x);

	//if the first item == the value return the location
	if(*(range.first)==x)
		return range.first-inputVec.begin();
	else
		return -1;
}

/***************************************************************
search
Use: calls a given search fuction on a vector looking for a vector of 
     numbers
Parameters: 1. inputVec:  Contains the address of the vector
	    2. searchVec:  The vector of int we are searching for
            3. p:  is the function name(linearSearch/binarySearch)
Returns: int(the number of times an item was found)
***************************************************************/
int search( const vector<int>& inputVec, const vector<int>& searchVec,
            int (*p)( const vector<int>&, int) )
{
	//set up function varibles
	int count=0;
	vector<int>::const_iterator searchNumber=searchVec.begin();

	//while it is not at the end of the search vector
	while(searchNumber!=searchVec.end())
	{
		//if the return was not -1 increase the count
		if((*p)(inputVec,*searchNumber)!=-1)
			count++;
		//advance the iterator
		searchNumber++;
	}

	//returns the final count of times found
	return count;
}

/***************************************************************
sortVector
Use: to sort a vector using sort found in algorithm
Parameters: 1. inputVec:  Contains the address of the vector
Returns: void
***************************************************************/
void sortVector (vector<int>& inputVec)
{
	//uses sort from <algorithm>
	sort(inputVec.begin(),inputVec.end());
}

/***************************************************************
printStat
Use: prints the % of items found to two decimal places
Parameters: 1. totalSucCnt:  number of items found
            2. vec_size:  size of the search vector
Returns: void
***************************************************************/
void printStat (int totalSucCnt, int vec_size)
{
	//casts it to float and displays
	cout<<"Successful searches: "<<fixed<<setprecision(2)<<(float)totalSucCnt/vec_size*100<<"%"<<endl;
}

/***************************************************************
print_vec
Use: prints out the vector with the correct formating
Parameters: 1. vec:  Contains the address of the vector
Returns: void
***************************************************************/
void print_vec( const vector<int>& vec )
{
        //Set starting value
        vector<int>::const_iterator currentPlace=vec.begin();

        //loop until end of vector
        while(currentPlace!=vec.end())
        {

                //prints the current value with spaces infront
                cout<<setw(ITEM_W)<<*currentPlace;

                //checks if it has reached the last item of the row
                if((currentPlace-vec.begin()+1)%NO_ITEMS==0)

                        //carriage return
                        cout<<endl;

                //shifts to next item and increases item count
                currentPlace++;
        }

        //extra space to match output
        cout<<endl;

        return;
}

int main()
{
    vector<int> inputVec(DATA_SIZE);
    vector<int> searchVec(SEARCH_SIZE);
    genRndNums(inputVec, DATA_SEED);
    genRndNums(searchVec, SEARCH_SEED);

    cout << "----- Data source: " << inputVec.size() << " randomly generated numbers ------" << endl;
    print_vec( inputVec );
    cout << "----- " << searchVec.size() << " random numbers to be searched -------" << endl;
    print_vec( searchVec );

    cout << "\nConducting linear search on unsorted data source ..." << endl;
    int linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on unsorted data source ..." << endl;
    int binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    sortVector( inputVec );

    cout << "\nConducting linear search on sorted data source ..." << endl;
    linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on sorted data source ..." << endl;
    binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    return 0;
}
