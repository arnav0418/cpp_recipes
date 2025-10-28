#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int test_cases;
    cin >> test_cases;

    vector<string> results;

    while(test_cases--)
    {
        int n;
        cin >> n;

        string s,t;
        cin >> s >> t;

        vector<int> count(26,0);

        for(char c: s) count[c - 'a']++;
        for(char c: t) count[c - 'a']--;

        int flag = 0;

        for(int x: count)
        {
            if(x != 0) 
            {
                results.push_back("NO");
                flag = 1;
                break;
            }
        }

        if(!flag) results.push_back("YES");
    }

    for(auto result: results)
    {
        cout << result << endl;
    }

    return 0;
}