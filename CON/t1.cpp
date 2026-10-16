#include<iostream>
#include<thread>
#include<chrono>
#include<vector>
using namespace std;

void worker(int i = 0 )
{
    cout<< "worker " << i <<"started\n";
    this_thread::sleep_for(chrono::seconds(5));
    
    cout<< "worker " << i <<" FINISHED\n";
}
class emp{
    public:
    void worker()
    {
        cout<<"class emp wworker has started\n";
        this_thread::sleep_for(chrono::seconds(5));
        cout<<"class emp wworker has FINISHED\n";
    }

    static void work()
    {
        cout<<"class emp wwor has started\n";
        this_thread::sleep_for(chrono::seconds(5));
        cout<<"class emp wwor has FINISHED\n";
    }
};
int main(){

    // thread T1(worker);
    // emp e1;
    // thread T1(&emp::worker , &e1); //non static memeber fun
    // thread T1(&emp::work); //non static memeber fun
    cout<<"Main Befoore join\n";
    // thread T1([](){
    //     cout<<"lambda worker thread";
    // });
    // T1.join();
    vector<thread> th;
    for(int i = 0; i<4;i++)
    {
        th.emplace_back(worker,i);
    } 
    for(auto &t : th)
        t.join();
        
    cout<<"Main After join\n";
    return 0;
}