#include <map>
#include<iostream>

using namespace std;

//Displays map
void showMap(map<int,int> x)
{
	map<int,int>::iterator mapit=x.begin();

	for(;mapit!=x.end();mapit++)
		cout<<mapit->second<<" ";

	cout<<endl;
}

//Performs a linear search on map for the value
bool mysearch(map<int,int> currentmap, int value)
{
	map<int,int>::iterator mapit=currentmap.begin();

	for(;mapit!=currentmap.end();mapit++)
		if(mapit->second==value)
			return true;
	return false;
}

int main()
{
//variables
	map<int,int> mymap;
	int value;

//loads map
	for(int x=0;x<10;x++)
		mymap.insert(make_pair(x,x+1));
//displays map
	showMap(mymap);

//gets search value from user
	cout<<"Enter a # to search for(0 to exit): ";
	cin>>value;

//will run searches untill the user exits
	while(value!=0)
	{
//performs my search function which returns a bool
		if(mysearch(mymap,value))
			cout<<"Found "<<value<<endl;
		else
			cout<<"Did not Find "<<value<<endl;

//requests value
		cout<<"Enter a # to search for(0 to exit): ";
		cin>>value;
	}
	return 0;
}
