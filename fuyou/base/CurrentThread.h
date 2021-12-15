#ifndef _CURRENT_THREAD_H
#define _CURRENT_THREAD_H
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>

namespace fuyou
{
    
namespace CurrentThread{
extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread const char* t_threadName;
extern __thread int t_tidStringLen;


void cacheTid();

inline int tid(){
    if(__builtin_expect(t_cachedTid == 0, 0)){
        cacheTid();
    }
    return t_cachedTid;
}



inline const char* tidString(){
    return t_tidString;
}

inline int tidStringLen(){
    return t_tidStringLen;
}

inline const char* name(){
    return t_threadName;
}

}
} // namespace fuyou

#endif