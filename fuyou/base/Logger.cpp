#include "Logger.h"
#include <time.h>
#include <sys/time.h>
#include <iostream>
namespace fuyou
{
static AsynLogging* _AsynLogger;
static pthread_once_t once_control = PTHREAD_ONCE_INIT;
std::string Logger::logFileName = "/home/hqin/fuyou/fuyou/base/log/fuyou.log";
void once_init(){
    _AsynLogger = new AsynLogging(Logger::getLogFileName());
    _AsynLogger -> start();
}

void _output(const char* msg, const int len){
    pthread_once(&once_control, once_init);
    _AsynLogger -> append(msg, len);
}

Logger::Impl::Impl(const char* filename, int line):_stream(),line(line),filename(filename){
    formatTime();
}

void Logger::Impl::formatTime(){
    struct timeval tv;
    time_t time;
    char str_t[26] = {0};
    gettimeofday(&tv, nullptr);
    time = tv.tv_sec;
    struct tm* p_time = localtime(&time);
    strftime(str_t, 26, "[%Y-%m-%d %H:%M:%S] \n", p_time);
    _stream << str_t;
}

Logger::Logger(const char* filename, int line):_impl(filename, line){
}

Logger::~Logger(){
    _impl._stream << '[' << _impl.filename << ':' << _impl.line << ']' << '\n';
    const Logstream::logbuf& buf(stream().getBuf());
    _output(buf.getData(), buf.getLen());
    //debug used
    // for(int i = 0; i < buf.getLen(); ++ i){
    //     std::cout << (char)*(buf.getData() + i);
    // }
    fwrite(buf.getData(), sizeof(char), buf.getLen(), stdout);
}
} // namespace fuyou
