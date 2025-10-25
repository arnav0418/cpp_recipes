#include <iostream>
#include <cmath>
#include <string>
using namespace std;

bool armstrong(int num)
{
    int sum = 0;
    int m = num;
    int count = 0;

    count = to_string(num).length();

    while(m>0)
    {
        sum += int(pow(m%10,count));
        m/=10;
    }

    return sum==num;
}

int main()
{
    cout<<armstrong(153);
    return 0;
}