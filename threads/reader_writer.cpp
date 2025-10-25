#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

using namespace std;

class semaphore
{
    int count;
    mutex mtx;
    condition_variable cv;

    public:

    semaphore(int permits)
    {
        count = permits;
    }

    void aquire()
    {
        unique_lock<mutex> lock(mtx);

        while(count<=0)
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

int resource = 0;

int readCount = 0;
mutex readCountMutex;
semaphore sem(1);
mutex print;

void reader(int id)
{
    while(true)
    {
        readCountMutex.lock();
        readCount++;

        if(readCount == 1)
        {
            sem.aquire();
        }

        readCountMutex.unlock();

        print.lock();

        cout << "Reader " << id << " is reading data = " << resource << endl;

        print.unlock();

        this_thread::sleep_for(chrono::milliseconds(100));

        readCountMutex.lock();
        readCount--;

        if(readCount == 0)
        {
            sem.release();
        }

        readCountMutex.unlock();

        this_thread::sleep_for(chrono::milliseconds(200));
    }

}

void writer(int id)
{
    while(true)
    {
        sem.aquire();

        resource++;

        cout << "Writer " << id << " is writing data = " << resource << endl;

        this_thread::sleep_for(chrono::milliseconds(150));

        sem.release();

        this_thread::sleep_for(chrono::milliseconds(300));        
    }
}

int main()
{
    vector<thread> readers, writers;

    for(int i = 1; i<5; i++)
    {
        readers.emplace_back(reader,i);
    }

    for(int i = 1; i<3; i++)
    {
        writers.emplace_back(writer,i);
    }

    for(auto& t: readers) t.join();
    for(auto& t: writers) t.join();

    return 0;
}