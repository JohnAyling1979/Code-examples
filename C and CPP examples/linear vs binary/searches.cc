/***********************************************************
CSCI 340 - Assignment 1 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Jan. 31 11:59 pm

Purpose: This program show the different efficiency between
a linear and binary search of a vector
************************************************************/



//Added includes vector, iostream, and iomanip
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

//Added for cout,cin, and endl
using namespace std;

const int DATA_RANGE = 100;
const int DATA_SIZE = 100;
const int DATA_SEED = 7;
const int SEARCH_SEED = 9;
//Added NO_ITEMS and ITEM_W per assignment
const int NO_ITEMS = 10;
const int ITEM_W = 6;

/***************************************************************
linear_search
Use: search thru the vector for a certain element
Parameters: 1. inputVec:  Contains the address of the vector
            2. x:  The number which is being searched for
	    3. comparisons:  Keeps tracks of the # of comparisons
Returns: bool(true if found, false if not found)
***************************************************************/
bool linear_search(const vector<int>& inputVec, const int x, int& comparisons)
{
	//set starting values for the funtion
	vector<int>::const_iterator currentPlace=inputVec.begin();
	comparisons=0;

	//loop until at the end of the vector
	while(currentPlace!=inputVec.end())
	{
		//raise comparison count
		comparisons++;

		//test if values are =. Returns True on a match
		if(*currentPlace==x)
			return true;

		//shifts to the next element
		currentPlace++;
	}

	// if no match was ever found return false
	return false;
}

/***************************************************************
binary_search
Use:  perform a binary search on the vector.  Needs to be a sorted
      vector
Parameters: 1. inputVec:  Contains the address of the vector
            2. x:  The number which is being searched for
            3. comparisons:  Keeps tracks of the # of comparisons
Returns: boot(true if found, false if not found)
***************************************************************/
bool binary_search(const vector<int>& inputVec, const int x, int& comparisons)
{
	//sets the default valuse for first and last elements
	//mid is set to 0 untill ready to use
	int low=0;
	int high=inputVec.size()-1;
	int mid=0;

	//reset comparisons
	comparisons=0;

	//loops until low or high swaps places
	while(low<=high)
	{
		//increase the cout on comparisons and set the current middle
		comparisons++;
		mid=(low+(high-low)/2);

		//checks if the value at the middle matches the value
		if(inputVec.at(mid)==x)
			return true;

		//compares the value in the middle location and sets the new
		//high or low based on if the value is higher or lower
		if(inputVec.at(mid)<x)
			low=mid+1;
		else
			high=mid-1;
	}

	//if no matches returns false
	return false;
}

/***************************************************************
print_vec
Use: prints out the vector in a formated table
Parameters: 1. vec:  the address of the vector to be printed
Returns: nothing
***************************************************************/
void print_vec( const vector<int>& vec )
{
	//Set starting values
	vector<int>::const_iterator currentPlace=vec.begin();
	int columns=1;

	//loop until end of vector
	while(currentPlace!=vec.end())
	{
		//prints the current value with spaces infront
		cout<<setw(ITEM_W)<<*currentPlace;

		//checks if it has reached the last item of the row
		if(columns%NO_ITEMS==0)
		{
			//carriage return and reset item count
			cout<<endl;
			columns=0;
		}
		//shifts to next item and increases item count
		currentPlace++;
		columns++;

	}

	//extra space to match output
	cout<<endl;

	return;
}

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, bool (*search)(const vector<int>&, const int, int&) ) {
    int i, comparison=0, sum=0, found = 0;
    bool res;
    for (i=0; i<(int)searchVec.size(); i++) {
        res = search( inputVec, searchVec[i], comparison );
        sum += comparison;
        if ( res )
           found++;
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size()<< endl << endl;
}

int random_number() {
    return rand()%DATA_RANGE+1;
}

int main () {

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number);
    sort(inputVec.begin(), inputVec.end());
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize( it - inputVec.begin() );
    random_shuffle( inputVec.begin(), inputVec.end() );

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl;
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number);

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;

}


