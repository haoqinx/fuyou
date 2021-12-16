#include "nonecopyable.h"
#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#ifndef __LOGSTREAM_H
#define __LOGSTREAM_H
namespace fuyou
{
const int BUF_SIZE = 4096;
const int LARGE_BUF_SIZE = 1024 * 4096;

template<int size>
class Logbuf:nonecopyable{
public:
    Logbuf():cur(data){}
    ~Logbuf(){}
    void append(const char* info, size_t len){
        if(getLeft() >= len){
            memcpy(cur, info, len);
            cur += len;
        }
    }
    const char* getData() const{
        return data;
    }
    int getLeft(){
        return static_cast<int>(end() - cur);
    }

    int getLen()const {
        return static_cast<int>(cur - data);
    }

    char* getCur(){
        return cur;
    }
    void reset(){
        cur = data;
    }
    void clear(){
        memset(data, 0, sizeof(data));
    }
    void add(size_t len){
        cur += len;
    }
private:
    const char* end() const{
        return data + sizeof(data);
    }
    char data[size];
    char* cur;
};

class  Logstream:nonecopyable{
public:
    typedef Logbuf<BUFSIZ> logbuf;
    typedef Logstream Self;
    Logstream(){}
    ~Logstream(){}
    Self& operator<<(short);
    Self& operator<<(unsigned short);
    Self& operator<<(int);
    Self& operator<<(unsigned int);
    Self& operator<<(long);
    Self& operator<<(long long);
    Self& operator<<(float);
    Self& operator<<(double);
    Self& operator<<(unsigned long long);
    Self& operator<<(const void*);
    Self& operator<<(long double);
    Self& operator<<(char);
    Self& operator<<(const char*);
    Self& operator<<(const unsigned char*);
    Self& operator<<(const std::string&);
    
    void append(const char* data, int len){
        buffer.append(data, len + 1);
    }

    void resetBuffer(){
        buffer.reset();
    }
    const char* getinfo(){
        return buffer.getData();
    }
    const logbuf& getBuf()const{
        return buffer;
    }
private:
    logbuf buffer;
    template<typename T> 
    void formatInteger(T);

    static const int fMaxIntegerSize = 32;
};
} // namespace fuyou

#endif