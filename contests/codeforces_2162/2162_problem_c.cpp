#include<iostream>
#include <vector>
using namespace std;

using ll = long long;

int highest_bit(ll x) 
{
    for (int b = 60; b >= 0; b--) 
    {
        if ( (x >> b) & 1 ) return b;
    }

    return -1;
}

int main()
{
    vector<int> count_xor;
    vector<vector<ll>> value_xor;

    int test_cases;
    cin >> test_cases;

    while(test_cases--)
    {
        ll a,b;
        cin >> a;
        cin >> b;

        int ha = highest_bit(a);
        int hb = highest_bit(b);

        if (hb > ha) 
        {
            count_xor.push_back(-1);
            value_xor.push_back({});

            continue;
        }

        if(a == b) 
        {
            count_xor.push_back(0);
            value_xor.push_back({});

            continue;
        }

        ll diff = a^b;

        if(diff <= a)
        {
            count_xor.push_back(1);
            value_xor.push_back({diff});

            continue;
        }

        ll x1 = -1;
        ll x2 = -1;

        for (ll i = 0; i <= a; i++) 
        {
            ll a1 = a ^ i;
            ll diff2 = a1 ^ b;

            if (diff2 <= a1) 
            {
                x1 = i;
                x2 = diff2;
                break;
            }
        }

        if (x1 == -1) 
        {
            count_xor.push_back(-1);
            value_xor.push_back({});
        } 
        else 
        {
            count_xor.push_back(2);
            value_xor.push_back({x1, x2});
        }

        
    }

    for (int i = 0; i < count_xor.size(); i++) 
    {
        int k = count_xor[i];
        if (k == -1) 
        {
            cout << -1 << '\n';
        } 
        else 
        {
            cout << k << '\n';
            if (k > 0) 
            {
                for (int j = 0; j < value_xor[i].size(); j++) 
                {
                    cout << value_xor[i][j];
                    if (j + 1 != (int)value_xor[i].size()) cout << ' ';
                }
                cout << '\n';
            }
        }
    }

    return 0;
}