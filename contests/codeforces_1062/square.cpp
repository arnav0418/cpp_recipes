#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int test_cases;
    cin >> test_cases;

    vector<string> result;

    while(test_cases--)
    {
        int a,b,c,d;

        cin >> a >> b >> c >> d;

        if(a == b && b == c && c == d) result.push_back("YES");
        else result.push_back("NO");
    }

    for(auto r: result)
    {
        cout << r << endl;
    }

    return 0;
}