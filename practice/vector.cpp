#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec = {10, 20, 30, 40, 50};

    // Using vec.begin() to traverse the vector
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Using range-based for loop for the same effect
    for (const int& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;

    // return 0;


    vector<int> v;
    int n = 3476383;
    while(n>0)
    {
        v.push_back(n%10);
        n/=10;
        cout<<n<<endl;
    }

    cout<<(-11%10);

}
