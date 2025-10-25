#include <iostream>
#include <thread>

using namespace std;

int variable = 0;

void write1()
{
    variable = 1;
}
void write2()
{
    variable = 2;
}

int main()
{
    thread t1(write1);
    thread t2(write2);

    t1.join();
    t2.join();

    cout << "variable value: " << variable;

    return 0;
}