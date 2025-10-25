#include <iostream>
#include <vector> // For std::vector
#include <algorithm> // For std::max

using namespace std;

class Solution{
  public:
    int minJumps(int arr[], int n){
        // Your code here
        
        int curr_index = 0;
        int jump_count = 0;
        
        if(arr[curr_index]==0)
        {
            return -1;
        }
        

        while(curr_index<n)
        {
            int max_jump = arr[curr_index];
            int optimal_jump = curr_index;
            
            for(int i = curr_index+1; i<curr_index+max_jump; i++)
            {
                if( arr[i]+i > arr[curr_index+max_jump]+curr_index+max_jump)
                {
                    max_jump = arr[i];
                    optimal_jump = i;
                }
            }
            
            curr_index += optimal_jump;
            jump_count++;
        }
        
        return jump_count;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n); // Use vector instead of raw array
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        Solution obj;
        cout << obj.minJumps(arr.data(), n) << endl; // Pass raw array pointer
    }
    return 0;
}




/*
if (n == 0 || arr[0] == 0) {
        return -1;  // If the first element is 0, we cannot move.
        }
        
        int jumps = 0;
        int curr_index = 0;
        int max_jump = arr[curr_index];
        int optimal_jump = 0;
        
        for( int i = 1; i<n; i++)
        {
            optimal_jump = max(max_jump+curr_index+arr[max_jump+curr_index],i+arr[i]);
            
            if( i == curr_index+max_jump)
            {
                jumps++;
                curr_index+=optimal_jump;
                
                if(curr_index>=n)
                {
                    return jumps;
                }
            }
            
            max_jump = arr[curr_index];
          
        }
        
        return -1;  // If we finish the loop and can't reach the end*/