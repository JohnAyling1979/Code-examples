#include <iostream>

using namespace std;

int loop_sum( int n )
{
    int sum = 0;

    while ( n > 0)
        sum += n--;

    return sum;
}

int recursive_sum( int n )
{
    if ( n <= 0 )
        return 0;

    return recursive_sum( n-1 ) + n;
}

int explicit_sum(int n)
{
    return (n*(n+1))/2;
}

int main() {
    int n;

    cout<<"Enter number:";
    cin>>n;
    cout << loop_sum( n ) << endl;

    cout << recursive_sum( n) << endl;

    cout<< explicit_sum(n)<<endl;
    return 0;
}
