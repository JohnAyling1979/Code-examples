/***********************************************************
CSCI 340 - Assignment 9 - Spring 2017

Progammer:	John Ayling
Z-ID:		z981329
Section:	3
TA:		Khaja Anwar Ali Siddiqui
Date Due:	May. 1 11:59 pm

Purpose: To build an adjency list from a matrix and then
	transverse that graph
************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "graph.h"

using namespace std;

#define ASSIGNMENT9_TEST
//private member function
/***************************************************************
graph::depth_first(int v)
Use:		To tranverse through the graph(recursive)
Parameters:	1. int v: The current vertice
Returns:	None
***************************************************************/
void graph::depth_first( int v)
{
	//assign the counter and then increase it
	order.at(v)=counter++;

	//go through the adj_list for that vectice
	//and if it is not not visited make an edge and
	//call depth first on that vertice
	for(list<int>::iterator u=adj_list.at(v).begin();u!=adj_list.at(v).end();u++)
	{
		if(order.at(*u)==0)
		{
			edges.push_back(make_pair(v,*u));
			depth_first(*u);
		}
	}
}

//public member functions
/***************************************************************
graph::topological()
Use:		To print out a topological order using 
		an adjmatrix
Parameters:	None
Returns:	None
***************************************************************/
void graph::topological()
{
	//variables
	vector<vector<int> > matrix;//could of been put in the class
	list<int>::iterator loc;
	vector<int> visited;
	vector<int> row;//used to build matrix

	//sized the visited matrix
	visited.resize(size);

	//build matrix could be moved to it's own function
	for(int x=0;x<size;x++)
	{
		loc=adj_list.at(x).begin();
		for(int y=0;y<size;y++)
			//if the value in the adjlist=the vertice
			//add a 1 to the row or else put a 0
			if(*loc==y)
			{
				row.push_back(1);
				loc++;
			}
			else
				row.push_back(0);

		//add the built row to the matrix
		matrix.push_back(row);

		//clear the row
		row.clear();
	}

	//print the matrix
	cout<<"ADJ MATRIX"<<endl;
	for(int x=0;x<size;x++)
	{
		for(int y=0;y<size;y++)
			cout<<matrix.at(x).at(y)<<" ";
		cout<<endl;
	}
	cout<<endl;

	//sort
	//header
	cout<<"Topological Sort"<<endl;

	//variables
	int sum,col;

	//do it for all vertices
	for(int i=0;i<size;i++)
	{
		//pre column location
		col=-1;
		do
		{
			//increase col and reset sum
			col++;
			if(col==size)
	                {
        	                cout<<"error graph has a cycle. Topological sort can not be done"<<endl;
                	        return;
	                }
			sum=0;
			//for the current column add all the values
			for(int row=0;row<size;row++)
				sum+=matrix.at(row).at(col);
		//if the sum was not 0 or if we had already visited it
		//go to the next one
		if(col==size)
		{
			cout<<"error graph has a cycle. Topological sort can not be done"<<endl;
			return;
		}
		}while(sum!=0 || visited.at(col)==1);

		//print out the found vertice
		cout<<labels.at(col)<<" ";

		//mark as visted
		visited.at(col)=1;

		//clear the row for the found vertice
		for(int x=0;x<size;x++)
			matrix.at(col).at(x)=0;
	}
	cout<<endl;
}


/***************************************************************
graph::graph()
Use:		Constructor for class
Parameters:	1. const char* filename: The file containing the
		adj matrix
Returns:	None
***************************************************************/
graph::graph( const char* filename )
{
	//file variables
	ifstream infile;

	//open the input file
	infile.open(filename,ifstream::in);

	//if it opened process the file
	//else display an error message
	if(infile.is_open())
	{
		//variables
		int innum;
		char inchar;
		list<int> temp;

		//read from file and
		//save it to size
		infile>>size;

		//get the next line and
		//save the vector lables
		for(int i=0;i<size;i++)
		{
			infile>>inchar;
			labels.push_back(inchar);
		}

		//for each row
		for(int i=0;i<size;i++)
		{
			//get the vertice
			infile>>inchar;

			//for each column
			for(int n=0;n<size;n++)
			{
				//get the number
				//if it is 1 add that loc to the
				//linked list
				infile>>innum;
				if(innum==1)
					temp.push_back(n);
			}
			//add the linked to the adj list
			adj_list.push_back(temp);

			//clear the list for the next row
			temp.clear();
		}
		//close the file
		infile.close();
	}else
	{
		//error message if file did not open
		cout<<"File did not open"<<endl;
	}
}

/***************************************************************
graph::~graph()
Use:		Destructor for class
Parameters:	None
Returns:	None
***************************************************************/
graph::~graph()
{
// nothing to clean up
// closed file in constuctor
}

/***************************************************************
graph::get_size()
Use:		Return the number of vertices for non member
		function(was not needed for this assignment)
Parameters:	None
Returns:	int: number of vertices in the graph
***************************************************************/
int graph::get_size() const
{
	return size;
}

/***************************************************************
graph::traverse()
Use:		To call depthfirst function and then display the
		output
Parameters:	None
Returns:	None
***************************************************************/
void graph::traverse( )
{
	//inisualize variables
	order.clear();
	order.resize(size);
	edges.clear();
	counter=1;
	int v=0;
	int loc;

	//header
	cout<<"------- travere of graph ------"<<endl;

	//go to each vertice
	while(v<size)
	{
		//if the current vertice has not been visited
		//call depth_first on that vertice
		if(order.at(v)==0)
			depth_first(v);

		//set v to the next vertice
		v++;
	}

	//print the vertices in order
	for(int i=1;i<=size;i++)
	{
		//reset to the start for the order vector
		loc=0;

		//find the next vertice location
		while(order.at(loc)!=i)
			loc++;

		//print the label for the found loc
		cout<<labels.at(loc)<<" ";
	}
	cout<<endl;

	//print the edges in order
	for(vector<pair<int,int> >::iterator i=edges.begin();i!=edges.end();i++)
		cout<<"("<<labels.at(i->first)<<", "<<labels.at(i->second)<<") ";
	cout<<endl;

	//footer
	cout<<"--------- end of traverse -------"<<endl<<endl;
}

/***************************************************************
graph::print() const
Use:		To display the graph info
Parameters:	None
Returns:	None
***************************************************************/
void graph::print ( ) const
{
	//header
	cout<<endl<<"Number of vertices in the graph: "<<size<<endl<<endl;
	cout<<"-------- graph -------"<<endl;

	//go through each vector
	for(int v=0;v<size;v++)
	{
		//print the vector from the label
		cout<<labels.at(v)<<": ";

		//go through the list for that vector and print it
		//will not print a , after the last vertice
		for(list<int>::const_iterator l=adj_list.at(v).begin();l!=adj_list[v].end();l++)
		{
			cout<<labels.at(*l);
			if(++l!=adj_list[v].end())
				cout<<", ";
			l--;
		}
		cout<<endl;
	}

	//footer
	cout<<"------- end of graph ------"<<endl<<endl;
}


#ifdef 	ASSIGNMENT9_TEST

int main(int argc, char** argv) {
    if ( argc < 2 ) {
        cerr << "args: input-file-name\n";
        return 1;
    }

    graph g(argv[1]);

    g.print();

    g.traverse();

//  made a topological function for my self using an adjence matrix
    g.topological();

    return 0;
}

#endif
