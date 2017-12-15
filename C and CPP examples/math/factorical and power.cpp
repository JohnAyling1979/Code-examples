#include <iostream>

using std::cout;
using std::cin;
using std::endl;

unsigned long int fact(int);
unsigned long int power(int);

int main()
{
	int number;

	do
	{
		cout<<"Enter number"<<endl;
		cin>>number;
	}while(number<=0);
	cout<<number<<"!="<<fact(number)<<endl;
	cout<<"2"<<"^"<<number<<"="<<power(number)<<endl;


	return 0;
}

unsigned long int fact(int x)
{
	if(x<=1)
		return 1;
	return x*fact(x-1);
}

unsigned long int power(int number)
{
	if(number<=1)
		return 2;
	return 2*power(number-1);
}
