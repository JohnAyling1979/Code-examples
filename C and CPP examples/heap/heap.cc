/***********************************************************
CSCI 340 - Assignment 7 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Apr. 6 11:59 pm

Purpose: To create heap out of a given vector and then sort
         that heap base on a given comparison
************************************************************/
//needed includes
#include<iostream>//cout
#include<vector>//vector
#include<algorithm>//random_suffle and reverse
#include<iomanip>//setw

//added to save typing
using namespace std;

const int HEAP_SIZE = 50;

//Declaring Functions
bool less_than(int e1,int e2){return e1<e2;}
bool greater_than(int e1,int e2){return e1>e2;}

void print_vector(vector<int>&,int,int);
void build_heap(vector<int>&,int,bool(*)(int,int));
void heapify(vector<int>&,int,int,bool(*)(int,int));
void heap_sort(vector<int>&,int,bool(*)(int,int));
int extract_heap(vector<int>&,int&,bool(*)(int,int));

int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}

/***************************************************************
print_vector
Use: To print out the vector in a formated manner
Parameters:     1. vector<int>& v: The vector passed by reference
		2. int pos: The starting pos to print from
		3. int size: The number of elements
Returns: None
***************************************************************/
void print_vector(vector<int>& v,int pos, int size)
{
	//go thru the vector printing out the elements
	for(;pos!=size+1;pos++)
	{
		//5 spaces per value
		cout<<setw(5)<<v.at(pos);
		//8 per line
		if(pos%8==0)
			cout<<endl;
	}
	cout<<endl;
}

/***************************************************************
build_heap
Use: Used to build a heap based on the comparison givin
Parameters:     1. vector<int>& v: The vector passed by reference
                2. int heap_size: The size of the heap
                3. bool(*compar)(int,int): a function that takes
		   2 ints and return a bool
Returns: None
***************************************************************/
void build_heap(vector<int>& v,int heap_size,bool (*compar)(int,int))
{
	//set the pos to before the first leaf
	int pos=heap_size/2;
	//while not at pos 0 correct the heap
	while(pos!=0)
	{
		//apply the heap rules
		heapify(v,heap_size,pos,compar);
		//go up the next pos
		pos--;
	}
}

/***************************************************************
heapify
Use: Used to enforce the heap rules based on the comaprison
Parameters:     1. vector<int>& v: The vector passed by reference
                2. int heap_size: The size of the heap
		3. int r: root location of the heap
                4. bool(*compar)(int,int): a function that takes
                   2 ints and return a bool
Returns: None
***************************************************************/
void heapify(vector<int>& v,int heap_size,int r,bool (*compar)(int,int))
{
	//a leaf of the tree
	if(r>heap_size/2)
		return;

	//create a variable for child
	int c=r*2;

	//check if 2 kids
	if(c<heap_size)
		//compare the two children. if true move to second
		//child
		if(compar(v.at(c+1),v.at(c)))
			c++;

	//compare the child to the parent
	//if true swap the value and down heap
	if(compar(v.at(c),v.at(r)))
	{
		v.at(0)=v.at(c);
		v.at(c)=v.at(r);
		v.at(r)=v.at(0);
		//heap down
		heapify(v,heap_size,c,compar);
	}



/*my way
	//onlt one child
	if(r*2+1>heap_size)
	{
		//compar the one child to its parent
		if(compar(v.at(r*2),v.at(r)))
		{
			//swap child and parent using location 0 as a temp loc
			v.at(0)=v.at(r*2);
			v.at(r*2)=v.at(r);
			v.at(r)=v.at(0);
			//heap down
			heapify(v,heap_size,r*2,compar);
		}
	//2 children
	}else
	{
		//compar the 2 children
		if(compar(v.at(r*2),v.at(r*2+1)))
		{
			//first child
			if(compar(v.at(r*2),v.at(r)))
			{
				//swap
				v.at(0)=v.at(r*2);
				v.at(r*2)=v.at(r);
				v.at(r)=v.at(0);
				//heap down
				heapify(v,heap_size,r*2,compar);
			}
		}else
		{
			//second child
			if(compar(v.at(r*2+1),v.at(r)))
			{
				//swap
				v.at(0)=v.at(r*2+1);
				v.at(r*2+1)=v.at(r);
				v.at(r)=v.at(0);
				//heap down
				heapify(v,heap_size,r*2+1,compar);
			}
		}
	}
*/
}

/***************************************************************
heap_sort
Use: Sort the heap based on the comparison
Parameters:     1. vector<int>& v: The vector passed by reference
                2. int heap_size: The size of the heap
                3. bool(*compar)(int,int): a function that takes
                   2 ints and return a bool
Returns: None
***************************************************************/
void heap_sort(vector<int>& v,int heap_size,bool(*compar)(int,int))
{
	//visit eash element in the heap
	for(int i=1;i<=HEAP_SIZE;i++)
		//extracte the value and append it to the adjusted
		//back location
		v.at(heap_size)=extract_heap(v,heap_size,compar);

	//reverse the order to correct the heap
	reverse(v.begin()+1,v.end());
}

/***************************************************************
extract_heap
Use: To remove the root and then replace it with the last one. Then
     heapify to fix the heap
Parameters:     1. vector<int>& v: The vector passed by reference
                2. int& heap_size: The size of the heap by reference
                3. bool(*compar)(int,int): a function that takes
                   2 ints and return a bool
Returns: the value that was in root
***************************************************************/
int extract_heap(vector<int>& v,int& heap_size,bool(*compar)(int,int))
{
	//save the value to return
	int value=v.at(1);

	//move last element to root
	v.at(1)=v.at(heap_size);
	//drop heap_size by one
	heap_size--;
	//down heap
	heapify(v,heap_size,1,compar);

	//return the saved value
	return value;
}
