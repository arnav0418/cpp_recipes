#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class dlist
{
    public:

    int key;
    int value;

    dlist* next;
    dlist* prev;

    dlist(int key, int value)
    {
        this->key = key;
        this->value = value;

        next = nullptr;
        prev = nullptr;
    }
};

class cache
{
    unordered_map<int,dlist*> key_node;
    int size;

    dlist* head;
    dlist* tail;

    public:

    cache(int size)
    {
        this->size = size;
        
        head = new dlist(-1,-1);
        tail = new dlist(-1,-1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if(!key_node.count(key))
        {
            cout << "Sorry the entry does not exist" << endl;
            return -1;
        }

        dlist* node = key_node[key];

        int value = node->value;

        removeNode(node);
        insertAtHead(node);

        return value;
    }

    void put(int key, int value)
    {
        if(key_node.count(key))
        {
            dlist* node = key_node[key];

            removeNode(node);
            insertAtHead(node);

            node->value = value;

            return;
        }

        if(key_node.size() == size)
        {
            dlist* lru = tail->prev;
            
            key_node.erase(lru->key);
            removeNode(lru);

            delete lru;
        }

        dlist* node = new dlist(key,value);
        key_node[key] = node;

        insertAtHead(node);

        return;        
    }

    private:

    void insertAtHead(dlist* node)
    {
        dlist* temp = head->next;

        temp->prev = node;
        head->next = node;

        node->next = temp;
        node->prev = head;
    }

    void removeNode(dlist* node)
    {
        dlist* nextNode = node->next;
        dlist* prevNode = node->prev;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

    }

    
};