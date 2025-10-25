#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>

using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv;
bool done = false;

void producer()
{
    for(int i = 0; i < 100; i++)
    {
        unique_lock<mutex> lock(mtx);

        buffer.push(i);
        cout << "Produced: " << i << endl;

        cv.notify_all();
    }

    done = true;
    cv.notify_all();
}

void consumer()
{
    unique_lock<mutex> lock(mtx);

    while(!buffer.empty() || !done)
    {
        while(buffer.empty() && !done)
        {
            cv.wait(lock);
        }

        while(!buffer.empty())
        {
            int val = buffer.front();
            buffer.pop();
            cout << "Consumed: " << val << endl;
        }
    }
}

int main()
{
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}