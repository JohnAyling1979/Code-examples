#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node
{
	friend class LinkedList;
	int data;
	Node * next;

	public:
		Node(int v,Node* n){data=v;next=n;}
};

class LinkedList
{
	private:
		Node* root;
		void reverse_print(const Node* n) const;
		void print_list(const Node* n) const;
	public:
		LinkedList(){root=NULL;}
		void reverse_print() const;
		void print_list() const;
		void add(int val);
};

#endif
