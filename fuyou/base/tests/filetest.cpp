#include "../FileUtil.h"
#include <iostream>
#include <pthread.h>
using namespace std;
using namespace fuyou;
void* work(void*args){
    FileUtil* f = (FileUtil*)args;
    const char* s = "asdasda\n";
    int cnt = 10;
    while(cnt --){
        f->append(s, sizeof(s));
        f->flush();
    }
    return nullptr;
}

int main(){
    FileUtil fu("./test.txt");
    pthread_t p1, p2, p3;
    pthread_create(&p1, nullptr, work, (void*)&fu);
    pthread_create(&p2, nullptr, work, (void*)&fu);
    pthread_create(&p3, nullptr, work, (void*)&fu);
    pthread_join(p1, nullptr);
    pthread_join(p2,nullptr);
    pthread_join(p3,nullptr);
    return 0;
}