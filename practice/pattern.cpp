#include <iostream>
using namespace std;

 void printPattern(int n)
{
    for(int i = 1; i<=n; i++)
    {
        for(int j = 1; j<=i; j++)
        {
            cout<<"*";
        }

        for(int j = 1; j<=2*(n-i); j++)
        {
            cout<<" ";
        }

        for(int j = 1; j<=i; j++)
        {
            cout<<"*";
        }

        cout<<endl;
    }
}

int main()
{
    int x;
    cout<<"Enter number: ";
    cin>>x;
    printPattern(x);
    return 0;
}