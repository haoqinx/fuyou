#include <iostream>
#include <thread>
#include <syscall.h>
#include <vector>
#include "../Logger.h"
using namespace std;
using namespace fuyou;

void* work(void*args){
    long long cnt = 1999;
    while(cnt --){
        LOG << "test info \t";
    }
    return nullptr;
}
class A{
public:
    int data;
    A(int d):data(d){cout << "A const" << endl;}
    ~A(){cout << "A deconst" << endl;}
    int getData(){return data;}
};

int main(){
    pthread_t p1;
    pthread_create(&p1, nullptr, work, nullptr);
    pthread_join(p1, nullptr);
    return 0;
}