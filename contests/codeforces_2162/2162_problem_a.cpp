#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int test_cases = 0;
    cin >> test_cases;

    vector<int> results;

    while(test_cases--)
    {
        int n;
        cin >> n;

        int result = 0;
        int x;

        for(int i = 0; i<n; i++)
        {
            cin >> x;
            result = max(result,x);
        }

        results.push_back(result);
    }

    for(int num: results)
    {
        cout << num << endl;
    }

    return 0;
}
