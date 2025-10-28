#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;


int main()
{
    int test_cases;
    cin >> test_cases;

    vector<vector<int>> results;

    while(test_cases--)
    {
        int n;
        cin >> n;

        vector<int> toys;

        bool hasEven = false;
        bool hasOdd = false;

        for(int i = 0; i < n; i++)
        {
            int x;
            cin >> x;

            if(x&1) hasOdd = true;
            else hasEven = true;

            toys.push_back(x);
        }

        if(hasEven && hasOdd) sort(toys.begin(),toys.end());

        results.push_back(toys);
    }

    for(auto result: results)
    {
        for(auto toy: result)
        {
            cout << toy << " ";
        }

        cout << endl;
    }

    return 0;
}