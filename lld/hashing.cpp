#include <iostream>
#include <vector>
#include <list>

using namespace std;

class hashMap
{
    private:

    static const int size = 10;
    vector<list<pair<int,int>>> table;

    int hash_function(int key)
    {
        return key % size;
    }

    public:

    hashMap()
    {
        table.resize(size);
    }

    void put(int key, int value)
    {
        int index = hash_function(key);

        for(auto& pair: table[index])
        {
            if(pair.first == key)
            {
                pair.second = value;
                return;
            }
        }

        table[index].push_back({key,value});
    }

    int get(int key)
    {
        int index = hash_function(key);

        for(auto& pair: table[index])
        {
            if(pair.first == key)
            {
                return pair.second;
            }
        }

        return -1;
    }

    void remove(int key)
    {
        int index = hash_function(key);

        auto& bucket = table[index];

        for(auto it = bucket.begin(); it != bucket.end(); it++)
        {
            if(it->first == key)
            {
                bucket.erase(it);
                return;
            }
        }
    }

    void display()
    {
        for(int i = 0; i < size; i++)
        {
            cout << i << ": ";

            for(auto& pair: table[i])
            {
                cout << "[" << pair.first << " -> " << pair.second << "] ";
            }

            cout << endl;
        }
    }
};

int main()
{
    hashMap map;
    map.put(1, 10);
    map.put(2, 20);
    map.put(12, 120); // same bucket as key 2 (collision handled)
    map.display();

    cout << "Get key 2: " << map.get(2) << endl;

    map.remove(2);
    cout << "After removing key 2:" << endl;
    map.display();

    return 0;

}