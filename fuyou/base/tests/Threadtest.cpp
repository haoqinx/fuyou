#include "../Thread.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "../CountDownLatch.h"
using namespace std;
using namespace fuyou;
void* work(void* args){
    CountDownLatch* c = reinterpret_cast<CountDownLatch*>(args);
    this_thread::sleep_for(chrono::seconds(random() % 10));
    cout << "notify ..." << endl;
    c->countDown();
    return nullptr;
}

void* start(void* args){
    CountDownLatch* c = reinterpret_cast<CountDownLatch*>(args);
    cout << "waiting..." << endl;
    c->wait();
    while(true){
        cout << ::syscall(SYS_gettid);
        cout << "start" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    return nullptr;
}
int main(){
    pthread_t p1, p2, p3, p4;
    CountDownLatch c(3);
    pid_t pp = pthread_create(&p1, nullptr, start, (void*)&c);
    pid_t p = pthread_create(&p2, nullptr, work, (void*)&c);
    p = pthread_create(&p3, nullptr, work, (void*)&c);
    p = pthread_create(&p4, nullptr, work, (void*)&c);
    pthread_join(p1,nullptr);
    pthread_join(p2,nullptr);
    pthread_join(p3,nullptr);
    pthread_join(p4,nullptr);
    return 0;
}