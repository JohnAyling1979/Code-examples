#include <iostream>
#include <string>

using namespace std;

string test(int);

int main()
{
	cout<<test(0)<<endl;
	cout<<test(5)<<endl;
	cout<<test(9)<<endl;
}

string test(int x)
{
	return "Yes\0 No\0 Maybe\0"+x;

}
