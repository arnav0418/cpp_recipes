#include <iostream>
#include<thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>

using namespace std;

class semaphore
{
    mutex mtx;
    condition_variable cv;
    int count;

    public:

    semaphore(int permits)
    {
        count = permits;
    }

    void aquire()
    {
        unique_lock<mutex> lock(mtx);

        while(count <= 0)
        {
            cv.wait(lock);
        }

        count--;
    }

    void release()
    {
        unique_lock<mutex> lock(mtx);

        count++;

        cv.notify_all();
    }
};

semaphore sem(3);
int resource = 0;
mutex sp;

void safePrint(string msg)
{
    lock_guard<mutex> lock(sp);

    cout << msg << endl;
}

void accessResource(int id)
{
    sem.aquire();

    safePrint("Thread " + to_string(id) + " entering");

    resource++;
    this_thread::sleep_for(chrono::milliseconds(100));

    safePrint("Thread " + to_string(id) + " exiting");

    sem.release();

}


int main()
{
    thread t1(accessResource, 1);
    thread t2(accessResource, 2);
    thread t3(accessResource, 3);
    thread t4(accessResource, 4);
    thread t5(accessResource, 5);

    t1.join(); 
    t2.join(); 
    t3.join(); 
    t4.join();
    t5.join();

    return 0;
}