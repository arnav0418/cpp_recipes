#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isPalindrome(string s)
{
    int left = 0;
    int right = s.length() - 1;

    while(left <= right)
    {
        if(s[left] != s[right]) return false;

        left++;
        right--;
    }

    return true;
}

int main()
{
    int test_cases;
    cin >> test_cases;

    vector<int> p_length;
    vector<vector<int>> p_indices;

    while(test_cases--)
    {
        int n;
        string s;

        cin >> n;
        cin >> s;

        if(isPalindrome(s))
        {
            p_length.push_back(0);
            p_indices.push_back({});

            continue;
        }

        bool found = false;

        for(int mask = 0; mask < (1<<n); mask++)
        {
            string p;
            string remaining_s;

            vector<int> idx;

            for(int i = 0; i<n; i++)
            {
                if(mask & (1<<i))
                {
                    p.push_back(s[i]);
                    idx.push_back(i+1);
                }
                else
                {
                    remaining_s.push_back(s[i]);
                }
            }

            if(!is_sorted(p.begin(),p.end())) continue;

            if(isPalindrome(remaining_s))
            {
                p_length.push_back(idx.size());
                p_indices.push_back(idx);

                found = true;
                break;
            }

        }

        if(!found) 
        {
            p_length.push_back(-1);
            p_indices.push_back({});
        }


    }

    for(int i = 0; i<p_length.size(); i++)
    {
        if(p_length[i] == 0 || p_length[i] == -1)
        {
            cout << p_length[i] << endl;
            continue;
        }

        cout << p_length[i] << endl;

        for(int j = 0; j<p_indices[i].size(); j++)
        {
            cout << p_indices[i][j];

            if (j + 1 != p_indices[i].size()) cout << ' ';
        }

        cout << '\n';
    }

    return 0;
}