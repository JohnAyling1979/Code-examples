/***********************************************************
CSCI 340 - Assignment 5 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Mar. 9 11:59 pm

Purpose: To create a tree structure and then display that 
structure using order,pre order, and post order
************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "assignment5.h"

using namespace std;

const int MAX_SIZE = 40;
const int MAX_COUNT = 40;
const int WIDTH = 5;
const int ROW_SIZE = 8;

int mcount = 0;
int rcount = 0;

void display(int d) {
    if ( mcount < MAX_COUNT ) {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE ) {
            cout << endl;
            rcount = 0;
        }
    }
}


//comment out the define to use the main for assignment 6
//#define BINTREE_MAIN
//public methods of binTree
/***************************************************************
constructor
Use: on creation of the object set root to NULL
Parameters: None
Returns: None 
***************************************************************/
binTree::binTree()
{
	root=NULL;
}

/***************************************************************
insert
Use: Used to insert the value into the tree by calling the private
version
Parameters: 1. int value: the value to be inserted
Returns: None 
***************************************************************/
void binTree::insert( int value)
{
	insert(root,value);
}

/***************************************************************
height
Use: To give the numbet of levels below root by calling the private
version
Parameters: None
Returns: int: Number of levels below root
***************************************************************/
int binTree::height() const
{
	return height(root);
}

/***************************************************************
size
Use: To give the numbet of elements by calling the private
version
Parameters: None
Returns: int: Number of elements
***************************************************************/
unsigned binTree::size() const
{
	return size(root);
}

/***************************************************************
inorder
Use: To print out the elements in order by calling the private
version
Parameters: 1. vode (*func)(int):a funtion that takes int as a
parameter which in this case is use to display the value.
Returns: None
***************************************************************/
void binTree::inorder( void(*func)(int) )
{
	inorder(root,func);
}

/***************************************************************
preorder
Use: To print out the elements in preorder by calling the private
version
Parameters: 1. vode (*func)(int):a funtion that takes int as a
parameter which in this case is use to display the value.
Returns: None
***************************************************************/
void binTree::preorder( void(*func)(int) )
{
	preorder(root,func);
}

/***************************************************************
postorder
Use: To print out the elements in postorder by calling the private
version
Parameters: 1. vode (*func)(int):a funtion that takes int as a
parameter which in this case is use to display the value.
Returns: None
***************************************************************/
void binTree::postorder( void(*func)(int) )
{
	postorder(root,func);
}

//private versions of binTree
/***************************************************************
insert
Use: Used to insert the value into the tree
Parameters:	1. Node*& node: the referance of a node
		2. int value: the value to be inserted
Returns: None 
***************************************************************/
void binTree::insert( Node*& node, int value)
{	
	//if Root is NULL make at new node and
	//save the address into the given node
	if(node==NULL)
	{
		node=new Node(value);
		return;
	}
	//Both sides were full so go down the side 
	//with the least number of elements
	if(height(node->right)<height(node->left))
		insert(node->right,value);
	else
		insert(node->left,value);
}

/***************************************************************
height
Use: To give the numbet of levels below root
Parameters:	1. Node *node: the address of a node
Returns: int: Number of levels below root
***************************************************************/
int binTree::height( Node* node ) const
{
	//when the end is found remove that step down
	if(node==NULL)
		return -1;

	int left=height(node->left);
	int right=height(node->right);

	//return the higher of the two trees
	if(left>right)
		return left+1;
	else
		return right+1;
}

/***************************************************************
size
Use: To give the number of elements
Parameters:	1. Node *node: address of a node
Returns: unsigned: The total number of the elements in the tree
***************************************************************/
unsigned binTree::size( Node* node) const
{
	//if the end don't count it
	if(node==NULL)
		return 0;

	//go down each side and adding 1 for each
	return size(node->right)+size(node->left)+1;
}

/***************************************************************
inorder
Use: To print out the elements in order by going all the way down
the left prints the value and works towards the right
Parameters: 	1. Node *node: the address of a node
		2. vode (*func)(int):a funtion that takes int as a
parameter which in this case is use to display the value.
Returns: None
***************************************************************/
void binTree::inorder( Node* node , void(*func)(int))
{
	//If you are not at the end go down the left print
	//go down the right
	if(node!=NULL)
	{
		inorder(node->left,func);
		func(node->value);
		inorder(node->right,func);
	}
}

/***************************************************************
preorder
Use: To print out the elements in preorder by printing the value
then going down the left printing a value each time and then works 
right
Parameters: 	1. Node *node: the address of a node
		2. vode (*func)(int):a funtion that takes int as a
parameter which in this case is use to display the value.
Returns: None
***************************************************************/
void binTree::preorder( Node* node, void(*func)(int) )
{
	//if you are not at the end print the current value
	//go down the left and then the right
	if(node!=NULL)
	{
		func(node->value);
		preorder(node->left,func);
		preorder(node->right,func);
	}
}

/***************************************************************
postorder
Use: To print out the elements in order by going all the way down
the left prints the values of both leaves and works towards the right
Parameters: 	1. Node *node: the address of a node
		2. vode (*func)(int):a funtion that takes int as a
parameter which in this case is use to display the value.
Returns: None
***************************************************************/
void binTree::postorder( Node* node, void(*func)(int) )
{
	//if not at the end go down the left then the right
	//then print
	if(node!=NULL)
	{
		postorder(node->left,func);
		postorder(node->right,func);
		func(node->value);
	}
}




#ifdef BINTREE_MAIN
int main() {
    vector<int> v(MAX_SIZE);
    for (int i=1; i<MAX_SIZE; i++)
        v[i] = i;
    random_shuffle( v.begin(), v.end() );

    binTree bt;
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++)
        bt.insert( *it );

    cout << "Height: " << bt.height() << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "In order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.inorder( display );
    cout << "\n\nPre order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.preorder( display );
    cout << "\n\nPost order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.postorder( display );

    cout << endl;
    return 0;
}

#endif
