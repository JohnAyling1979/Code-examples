#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int mod(int a,int b)
{
	return ((float)a/(float)b-a/b)*b;
}

int main()
{
	int a,b;
	unsigned int tries=50000000;

	clock_t start=clock();
	for(unsigned int i=0;i<tries;i++)
	{
		a=rand()%100+1;
		b=rand()%100+1;
		mod(a,b);
	}
	clock_t stop=clock();
	cout<<"Fuction time was "<<double(stop-start)/CLOCKS_PER_SEC<<" seconds"<<endl;

	start=clock();
        for(unsigned int i=0;i<tries;i++)
        {
                a=rand()%100+1;
                b=rand()%100+1;
                a%b;
        }
        stop=clock();
        cout<<"      % time was "<<double(stop-start)/CLOCKS_PER_SEC<<" seconds"<<endl;
}
