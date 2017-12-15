#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class AddValue
{
	private: 
		int  toBeAdded;
	public:
		AddValue( int v ) { toBeAdded = v; }
		void operator () ( int& elem ) const { elem += toBeAdded; }
};

class print
{
	public:
		void operator()(int& elem) const {cout<<elem<< " ";}
};

int main ( ) 
{
	vector<int> vec;
	// some code to add values to vec
	vec.push_back(5);
	vec.push_back(10);
	vec.push_back(15);

        for(vector<int>::const_iterator i=vec.begin();i!=vec.end();i++)
                cout<<*i<<" ";
        cout<<endl;

	for_each( vec.begin(), vec.end(), AddValue(10) );

	for(vector<int>::const_iterator i=vec.begin();i!=vec.end();i++)
		cout<<*i<<" ";
	cout<<endl;

	for_each ( vec.begin(), vec.end(), AddValue( *(vec.begin()) ) );

        for(vector<int>::const_iterator i=vec.begin();i!=vec.end();i++)
                cout<<*i<<" ";
        cout<<endl;

	for_each(vec.begin(),vec.end(),print());
	cout<<endl;
}
