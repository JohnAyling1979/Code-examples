/***********************************************************
CSCI 340 - Assignment 6 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Mar. 27 11:59 pm

Purpose: To create a binary search tree, manipulate the tree
and then display that the using order,pre order, and post order
************************************************************/
#include <iostream>
#include "assignment5.h"
#include "assignment6.h"

//public methods
/***************************************************************
insert
Use: Used to call the private version of insert
Parameters:	1. int value: the value to be inserted
Returns: None
***************************************************************/
void BST::insert(int value)
{
	insert(root,value);
}

/***************************************************************
search
Use: Used to call the private version of search
Parameters:	1. int value: the value to search for
Returns: bool	true for found false for not found
***************************************************************/
bool BST::search(int value)
{
	return search(root,value);
}

/***************************************************************
remove
Use: Used to call the private version of remove
Parameters:	1. int value: the value to be removed
Returns: bool	true if removed false if not found
***************************************************************/
bool BST::remove(int value)
{
	return remove(root,value);
}

/***************************************************************
sumOfRange
Use: Used to call the private version of sumOfRange
Parameters:	1. int lower: the bottom value
		2. int upper: the top value
Returns: int	the sum of all the numbers
***************************************************************/
int BST::sumOfRange(int lower,const int upper)
{
	return sumOfRange(root,lower,upper);
}

//private
/***************************************************************
insert
Use: Used to insert the value into the tree
Parameters:	1. Node*& node: the referance of a node
		2. int value: the value to be inserted
Returns: None
***************************************************************/
void BST::insert(Node*& n,int value)
{
	//if node* is NULL make at new node and
	//set the pointer to that node
	if(n==NULL)
	{
		n=new Node(value);
		return;
	}

	//go down ether the left or right side based on the value
	if(value>n->value)
		insert(n->right,value);
	else
		insert(n->left,value);
}

/***************************************************************
search
Use: Used to search for a given value
Parameters:	1. Node*& n: pointer to the current node
		2. int value: the value to search for
Returns: bool	true for found false for not found
***************************************************************/
bool BST::search(Node*& n,int value)
{
	//if the current node value and search value match
	//return true
	if(n!=NULL)
	{
		if(value==n->value)
			return true;

		//continue down the side of the tree based on the value
		if(value>n->value)
			return search(n->right,value);
		if(value<n->value)
			return search(n->left,value);
	}

	//once it get to a leaf return false for that path
	return false;
}

/***************************************************************
remove
Use: Used to remove a given value
Parameters:	1. Node*& n: pointer to the current node
		2. int value: the value to be removed
Returns: bool	true if removed false if not found
***************************************************************/
bool BST::remove(Node*& n,int value)
{
	//if the current pointer is NULL return false
	if(n==NULL)
	{
		return false;
	}

	//go down the tree based on the value
	if(value<n->value)
		return remove(n->left,value);
	if(value>n->value)
		return remove(n->right,value);

	//value nether less or great so it must be ==
	//value was found
	//if the node has two children
	if(n->right!=NULL && n->left!=NULL)
	{
		//make a pointer for the
		//immediate predecessor
		Node* pred= n->left;

		//continue down the right side untill you hit the end
		while(pred->right!=NULL)
		{
			pred=pred->right;
		}

		//assign the predecessors value to the current node
		n->value=pred->value;

		//remove the duplicate by recalling the function
		remove(n->left,pred->value);
	//node is a leaf
	}else if(n->right==NULL && n->left==NULL)
	{
		//unallocate the memory
		delete n;
		//set the pointer to NULL
		n=NULL;
	//node has one child
	}else if(n->right!=NULL || n->left!=NULL)
	{
		//create a new pointer and have it
		//point to the same node as current
		Node* temp=n;

		//take the address of the child and make the current
		//pointer point to that node
		if(n->right!=NULL)
			n=n->right;
		else
			n=n->left;

		//free the memory for the node that was deleted
		delete temp;
	}

	//a node was removed so return true
	return true;
}

/***************************************************************
sumOfRange
Use: Used to get the sum of all the values with in a given range
Parameters:	1. Node*& n: pointer to the current node
		2. int lower: the bottom value
		3. int upper: the top value
Returns: int	the sum of all the numbers
***************************************************************/
int BST::sumOfRange(Node*& n,const int lower,const int upper)
{
	//if No Node return 0
	if(n==NULL)
		return 0;

	//return the total from both left and right
	//if the value is in the range add it to the return
	if(n->value>lower && n->value<upper)
		return n->value+sumOfRange(n->left,lower,upper)+sumOfRange(n->right,lower,upper);
	else
		return sumOfRange(n->left,lower,upper)+sumOfRange(n->right,lower,upper);
}
