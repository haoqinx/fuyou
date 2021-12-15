#ifndef _FILELOG_H
#define _FILELOG_H
#include "nonecopyable.h"
#include "MutexLock.h"
#include "FileUtil.h"
#include <memory>
namespace fuyou
{
class Filelog : nonecopyable{
public:
    Filelog(std::string name, int timeInterval);
    ~Filelog();

    void append(const char* str, int len);
    void flush();
    bool rollFile();
private:
    void append_unlocked(const char* str, int len);
    const std::string name;
    const int timeInterval;
    int count;
    std::string name;
    std::unique_ptr<MutexLock> mutex;
    std::unique_ptr<FileUtil> fp;
};
} // namespace fuyou


#endif