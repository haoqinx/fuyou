#include "Thread.h"
#include <assert.h>
#include <errno.h>
#include <linux/unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <memory>
#include <iostream>
using namespace std;

namespace fuyou
{
namespace CurrentThread{
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread const char* t_threadName = "default";
    __thread int t_tidStringLen = strlen("Thread") + 1;
}
pid_t getCurrentTid() {
    return static_cast<pid_t>(::syscall(SYS_gettid));
}


void CurrentThread::cacheTid(){
    if(t_cachedTid == 0){
        t_cachedTid = getCurrentTid();
        t_tidStringLen = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    }
}

Thread::Thread(const Threadfunc& func, const std::string& name)
   :startStatus(false),
    joinStatus(false),
    pid(0),
    tid(0),
    func(func),
    name(name),
    cond(1)
{
    if (name.empty()){
        char buf[32];
        snprintf(buf, sizeof buf, "Thread");
        this -> name = buf;
    }
}

void* startThread(void* args){
    ThreadData* data = static_cast<ThreadData*>(args);
    data -> runInThread();
    delete data;
    return nullptr;
}

void Thread::start(){
    assert(!startStatus);
    startStatus = true;
    ThreadData* data = new ThreadData(func, name, &tid, &cond);
    if(pthread_create(&pid, nullptr, &startThread, data)){
        startStatus = false;
        delete data;
    }
    else{
        cond.wait();
        assert(tid > 0);
    }
}

int Thread::join(){
    assert(startStatus);
    assert(!joinStatus);
    joinStatus = true;
    return pthread_join(pid, nullptr);
}

Thread::~Thread(){
    if(startStatus && ! joinStatus){
        pthread_detach(pid);
    }
}
} // namespace fuyou
