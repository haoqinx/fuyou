#ifndef __FILE_UTIL_H
#define __FILE_UTIL_H
#include "nonecopyable.h"
#include <string>
#include <stdio.h>
#include <stddef.h>
namespace fuyou
{
class FileUtil : nonecopyable{
public:
    explicit FileUtil(std::string filename):fp_(fopen(filename.c_str(), "ae")){
        setbuffer(fp_, buffer, sizeof(buffer));
    }
    ~FileUtil(){
        fclose(fp_);
    }
    void append(const char* line, const size_t len);
    void flush() { fflush(fp_); }
private:
    size_t write(const char* line, size_t len);
    FILE* fp_;
    char buffer[64 * 1024];
};
} // namespace fuyou

#endif