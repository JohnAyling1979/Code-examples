#include<iostream>
#include"tree.h"

using namespace std;

int main()
{
	Data input;
	tree mytree;
	char answer;

	do
	{
		cout<<"Enter Last Name: ";
		cin>>input.name;
		cout<<"Enter City: ";
		cin>>input.address;
		cout<<"Enter Salary: ";
		cin>>input.salary;

		mytree.insert(input);

		cout<<"Insert more?: ";
		cin>>answer;
	}while(answer=='y');



	mytree.printtree();

	return 0;
}
