#include <pthread.h>
#include <iostream>
#include <sys/syscall.h>
#include <unistd.h>

using namespace std;
//线程执行函数
void* func(void*args){
    cout << pthread_self() << endl;
    cout << ::syscall(SYS_gettid) << endl;
    return nullptr;
}
int main(){

    pthread_t p1;
    cout << "current process:" << ::syscall(SYS_gettid) << endl;
    pthread_create(&p1, nullptr, func, nullptr );
    pthread_join(p1, nullptr);
    return 0;
}