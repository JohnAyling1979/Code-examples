/***********************************************************
CSCI 340 - Assignment 4 - Spring 2017

Progammer: John Ayling
Z-ID: z981329
Section: 3
TA: Khaja Anwar Ali Siddiqui
Date Due: Mar. 1 11:59 pm

Purpose: To demestrate a stack class functionality using queues
************************************************************/

//needed includes
#include<iostream>
#include<string>
#include<iomanip>
#include"stack.h"

//added to save typing
using namespace std;

/***************************************************************
empty
Use: Used to check if the stack is empty
Parameters: None
Returns: bool true if both queues are empty otherwise false so 
the stack is empty 
***************************************************************/
bool Stack::empty() const
{
	//checks if both are empty
	if(q1.empty() && q2.empty())
		return true;
	else
		return false;
}

/***************************************************************
size
Use: Used to get the size of both queues
Parameters: None
Returns: int which is the total size of both queues or the size
of the stack 
***************************************************************/
int Stack::size() const
{
	//returns the total size
	return q1.size()+q2.size();
}

/***************************************************************
top
Use: Used to return the top value
Parameters: None
Returns: int which is the back value of the active queue or the
top of the stack 
***************************************************************/
int Stack::top()
{
	//finds the current queue and returns the value
	if(!q1.empty())
		return q1.back();
	else
		return q2.back();
}

/***************************************************************
push
Use: Used to add a value to the stack
Parameters: 1. const int val: pass by referance int which is 
               val to be added to stack
Returns: None 
***************************************************************/
void Stack::push(const int& val)
{
	//finds the current queue and adds the value to it
	if(!q1.empty())
		q1.push(val);
	else if(!q2.empty())
		q2.push(val);
	//if both were empty added it to q1
	else if(q1.empty() && q2.empty())
		q1.push(val);
	return;
}


/***************************************************************
pop
Use: Used to remove an item from the stack
Parameters: None
Returns: None 
***************************************************************/
void Stack::pop()
{
	//finds the current queue
	if(!q1.empty())
	{
		//moves all items from q1 to q2 execpt the last one
		while(q1.size()>1)
		{
			q2.push(q1.front());
			q1.pop();
		}
		//deletes last value
		q1.pop();
	}
	else
	{
		//moves all item from q2 to q1 execpt the last one
		while(q2.size()>1)
		{
			q1.push(q2.front());
			q2.pop();
		}
		//deletes the last value
		q2.pop();
	}
	return;
}

int main() 
{
    Stack s;
    string op;
    int val = 0;
 
   cout << "operation -- size front end" << endl;
   cin >> op;
   while ( !cin.eof() ) {
        if ( op == "push" ) {
            cin >> val;
            s.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            s.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl;
            return 1;
        }
        cout << setw(3) << s.size() << setw(5) << s.top() << endl;
        cin >> op;
    }

    while ( !s.empty() )
        s.pop();
    cout << "End -- size of Stack is: " << s.size() << endl;

    return 0;
}
