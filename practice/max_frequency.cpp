#include <iostream>
#include <vector>
#include <algorithm> // For max_element

using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int range = *max_element(nums.begin(),nums.end());

        vector<int> hash(range+1,0);

        for(const int &x : nums)
        {
            hash[x]++;
        }

        int max_frequency = 0;

        // sliding window logic
        for(int i=0; i<range+1; i++)
        {
            if(hash[i]==0)
            {
                continue;
            }

            int steps = k;
            int pointer = i;
            int sum = hash[i];

            while(steps!=0&&pointer>0)
            {
                pointer--;
                int cost=i-pointer;

                if(cost>steps || pointer==0)
                {
                    if(sum>max_frequency)
                    {
                        max_frequency = sum;
                    }
                    break;
                }

                if(hash[pointer]==0)
                {
                    continue;
                }

                if(hash[pointer]*cost>steps)
                {
                    sum+=int(steps/cost);
                    steps=0;
                    if(sum>max_frequency)
                    {
                        max_frequency = sum;
                    }
                    break;
                }

                sum+=hash[pointer];
                steps-=hash[pointer]*cost;

                if(sum>max_frequency)
                {
                    max_frequency = sum;
                }

            }
        }

        return max_frequency;
    }
};

int main() {
    Solution solution;

    // Test case 1
    vector<int> nums1 = {10};
    int k1 = 10;
    cout << "Test Case 1: " << solution.maxFrequency(nums1, k1) << endl; // Expected Output: 3

    return 0;
}
