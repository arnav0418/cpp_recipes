#include <iostream>
#include<vector>
#include<algorithm>
#include <numeric>

using namespace std;

int main() 
{
    int test_cases;
    cin >> test_cases;

    vector<long long> results;

    while (test_cases--) 
    {
        int n;
        cin >> n;

        vector<long long> arr, cost;

        for (int i = 0; i < n; ++i) 
        {
            int x;
            cin >> x;

            arr.push_back(x);
        }

        for (int i = 0; i < n; ++i) 
        {
            int x;
            cin >> x;

            cost.push_back(x);
        }

        vector<long long> dp(n);
        long long ans = 0;

        for (int i = 0; i < n; i++) 
        {
            dp[i] = cost[i];

            for (int j = 0; j < i; ++j) 
            {
                if (arr[j] <= arr[i]) dp[i] = max(dp[i], dp[j] + cost[i]);
            }
        }

        long long total_cost = accumulate(cost.begin(), cost.end(), 0LL);
        long long keep_best = *max_element(dp.begin(), dp.end());

        results.push_back(total_cost - keep_best);
    }

    for(auto result: results)
    {
        cout << result << endl;
    }

    return 0;
}
