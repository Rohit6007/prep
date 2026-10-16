#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
 mutex m;  

int counter = 0;
void increment()
{
    for(int i = 0; i<100000;i++)
    {
        m.lock();
        counter++;
        m.unlock();
    }
}
int main()
 {
    thread t1(increment);
    thread t2(increment);
    
    t1.join();
    t2.join();

    cout<<counter<<endl;

    return 0;
 }