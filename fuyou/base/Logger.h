#ifndef _LOGUTIL_H
#define _LOGUTIL_H
#include "nonecopyable.h"
#include "Logstream.h"
#include "AsynLogging.h"
#include <pthread.h>
namespace fuyou
{

class Logger{
public:
    Logger(const char* filename, int line );
    ~Logger();
    Logstream& stream(){
        return _impl._stream;
    }

    static void setLogFileName(std::string filename){
        logFileName = filename;
    }
    static std::string getLogFileName(){
        return logFileName;
    }
private:
    struct Impl{
        Impl(const char* filename, int line);
        void formatTime();
        Logstream _stream;
        int line;
        std::string filename;   
    };
    Impl _impl;
    static std::string logFileName;
    
};
} // namespace fuyou

#define LOG Logger(__FILE__, __LINE__).stream()
#endif