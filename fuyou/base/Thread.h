#ifndef _THREAD_H
#define _THREAD_H
#include <pthread.h>
#include <functional>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <memory>
#include "nonecopyable.h"
#include "CountDownLatch.h"
#include "CurrentThread.h"
#include <iostream>
using namespace std;
namespace fuyou
{

class Thread : nonecopyable{
public:
    typedef std::function<void()> Threadfunc;
    explicit Thread(const Threadfunc&, const std::string& str = std::string());
    explicit Thread(const Threadfunc&);
    ~Thread();
    void start();
    int join();
    bool started()const{
        return startStatus;
    }
    pid_t getTid() const{
        return tid;
    }
    const std::string& getName() const {
        return name;
    }

private:
    bool startStatus;
    bool joinStatus;
    pthread_t pid;
    pid_t tid;
    Threadfunc func;
    std::string name;
    CountDownLatch cond;
};

class ThreadData : nonecopyable{
public:
    typedef Thread::Threadfunc Threadfunc;
    Threadfunc func;
    std::string name;
    pid_t* tid;
    CountDownLatch* cond;

    ThreadData(const Threadfunc& func_, const std::string& name, pid_t* tid, CountDownLatch* cond)
                :func(func_), name(name), tid(tid), cond(cond){

    }
    void runInThread(){
        *tid = CurrentThread::tid();
        tid = nullptr;
        cond -> countDown();
        cond = nullptr;
        CurrentThread::t_threadName = name.empty() ? "Thread" : name.c_str();
        prctl(PR_SET_NAME, CurrentThread::t_threadName);
        func();
        CurrentThread::t_threadName = "Fin";
    }
};

} // namespace fuyou




#endif