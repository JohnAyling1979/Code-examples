/***********************************************************************
*                                                                      *
* Programer:	John Ayling                                            *
* Class:	CSCI 340 section 3                                     *
* Assignment:	0                                                      *
*                                                                      *
***********************************************************************/


#include <iostream>
#include "linkedlist.h"

using namespace std;

void LinkedList::reverse_print(const Node* n) const
{
	if(n==NULL)
		return;
	reverse_print(n->next);
	cout<<n->data<< ' ';
}

void LinkedList::reverse_print() const
{
	cout<<endl;
	reverse_print(root);
	cout<<endl;
}

void LinkedList::add(int val)
{
	if(root==NULL)
		root=new Node(val,NULL);
	else
	{
		Node* n=new Node(val,root);
		root=n;
	}
}

void LinkedList::print_list(const Node* n) const
{
	if(n==NULL)
		return;
	cout<<n->data<<' ';
	print_list(n->next);
}

void LinkedList::print_list() const
{
	cout<<endl;
	print_list(root);
	cout<<endl;
}

int main()
{
	LinkedList LL;

	LL.add(3);
	LL.add(5);
	LL.add(8);
	LL.add(4);
	LL.add(9);

	LL.print_list();

	LL.reverse_print();

	return 0;
}
