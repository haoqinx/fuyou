#include "Filelog.h"

namespace fuyou
{
Filelog::Filelog(const std::string name, int timeInterval)
                :name(name),
                timeInterval(timeInterval),
                count(0),
                mutex(new MutexLock()){
    fp.reset(new FileUtil(name));
}

Filelog::~Filelog(){}

void Filelog::append(const char* line, int len){
    MutexLockGuard lock(*mutex);
    append_unlocked(line, len);
}

void Filelog::append_unlocked(const char* line, int len){
    fp -> append(line, len);
    ++ count;
    if(count >= timeInterval){
        count = 0;
        fp -> flush();
    }
}

void Filelog::flush(){
    MutexLockGuard lock(*mutex);
    fp -> flush();
}
} // namespace fuyou
