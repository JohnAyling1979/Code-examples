/***********************************************************
CSCI 340 - Assignment 3 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Feb. 20 11:59 pm

Purpose: This program takes user input and displayes the prime
numbers within the given range.  Uses set container and performs
sieve algorithm to find prime numbers
************************************************************/

//Includes nessesary to run the program
#include<iostream>
#include<set>
#include<string>
#include<cctype>
#include<iomanip>
#include<algorithm>

//Given constants
const int NO_ITEMS=8;
const int ITEM_W=6;

//std name usage for less typing
using namespace std;

//Functor to be used in for_each to print
class print
{
	private:
		int column;
	public:
		print(){column=1;}
		void operator() (const int& elem)
		{
			cout<<setw(ITEM_W)<<elem;
			if(column%NO_ITEMS==0)
				cout<<endl;
			column++;
		}
};


/***************************************************************
sieve
Use: Fill a set based off a range and then perform the Sieve of
     Eratosthenes algorithm on that set
Parameters: 1. s:  Address of the set variable
            2. lower:  Starting number of the range
	    3. upper:  End number in the range
Returns: void
***************************************************************/
void sieve( set<int>& s, const int lower, const int upper)
{
	//Clears the set for a clean start
	s.clear();

	//fills the set for interger in the given range
	for(int i=lower;i<=upper;i++)
		s.insert(i);

	//Sieve algorithm.  Starts at 2 and goes till the square
	//is >= to the end vallue
	for(int outer=2;(outer)*(outer)<upper;outer++)
			//goes thru the set and removes any products	
			for(int inner=(outer)*2;inner<=upper;inner+=outer)
				s.erase(inner);

	return;
}

/***************************************************************
print_primes
Use: Prints the prime numbers into a formated output
Parameters: 1. s:  Address of the set variable
            2. lower:  Starting number of the range
	    3. upper:  End number in the range
Returns: void
***************************************************************/
void print_primes( const set<int>& s, const int lower, const int upper)
{
	//Match spacing on output
	cout<<endl;

	//Header line
	cout<<"There are "<<s.size()<<" prime numbers between "<<lower<<" and "<<upper<<":"<<endl;
	
	//Goes thru the set printing the value out using the given
	//valiables for spacing
	for_each(s.begin(),s.end(),print());

	//For spacing
	cout<<endl<<endl;

	return;
}

/***************************************************************
run_game
Use: Is the main driver program.  Takes user input and calls the 
     other funtions
Parameters: 1. s:  Address of the set variable
Returns: void
***************************************************************/
void run_game(set<int>& s)
{
	//Creates need variables
	int lower,upper;
	string answer;

	//main loop
	do
	{
		//verifing correct value loop
		do
		{
			lower=upper=0;
			cout<<"Please input lower bound and upper bound and hit enter (e.g. 10 100):"<<endl;
			cin>>lower;
			cin>>upper;
			cin.clear();
			cin.ignore(256,'\n');
		}while(lower>=upper);
		//call sieve to find the primes
		sieve(s,lower,upper);
		//calls print_primes to display output
		print_primes(s,lower,upper);
		//verifing correct value loop
		do
		{
			cout<<"Do you want to continue or not? Please answer yes or no and hit enter:"<<endl;
			cin>>answer;
			//makes answer lower case to be more user friendly
			for(unsigned int i=0;i<answer.length();++i)
				answer[i]=tolower(answer[i]);
		}while(answer!="no" && answer!="yes");
	}while(answer=="yes");

	return;
}

/***************************************************************
main
Use: Given main program
Parameters: none
Returns: 0 on completion
***************************************************************/
int main() {
    set<int> s;
    run_game(s);
    return 0;
}
