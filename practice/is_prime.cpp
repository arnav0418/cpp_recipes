#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(long long x)
{
    if(x<=1) return false;
    if(x<=3) return true;

    if(x % 2 == 0 || x % 3 == 0) return false;

    long long limit = sqrt(x);

    for(int i = 5; i<=limit; i+=6)
    {
        if(x%i==0 || x%(i+2)==0) return false;
    }

    return true;

}

int main()
{
    long long number;
    cout<<"Please enter a number: ";
    cin>>number;
    cout<<endl;

    if(isPrime(number)) 
    {
        cout<<"This is a Prime number";
        return 0;
    }

    cout<<"This is not a Prime number";

    return 0;


}