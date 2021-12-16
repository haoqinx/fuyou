#include "Logstream.h"
using namespace fuyou;

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;


template<typename T>
size_t convert(char* cur, T data){
    T tmp = data;
    char* p = cur;
    do{
        int lsd = static_cast<int>(tmp % 10);
        tmp /= 10;
        *p++ = zero[lsd];
    }while(tmp != 0);
    if(data < 0){
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(cur, p);
    return p - cur;
}

template<typename T>
void Logstream::formatInteger(T data){
    if(buffer.getLeft() >= fMaxIntegerSize){
        size_t len = convert(buffer.getCur(), data);
        buffer.add(len);
    }
}

Logstream& Logstream::operator<<(short data){
    return *this << static_cast<int>(data);
}
Logstream& Logstream::operator<<(unsigned short data){
    return *this << static_cast<unsigned int>(data);
}
Logstream& Logstream::operator<<(int data){
    formatInteger(data);
    return *this;
}
Logstream& Logstream::operator<<(unsigned int data){
    formatInteger(data);
    return *this;
}
Logstream& Logstream::operator<<(long data){
    formatInteger(data);
    return *this;
}

Logstream& Logstream::operator<<(unsigned long data){
    formatInteger(data);
    return *this;
}

Logstream& Logstream::operator<<(long long data){
    formatInteger(data);
    return *this;
}
Logstream& Logstream::operator<<(float data){
    if (buffer.getLeft() >= fMaxIntegerSize) {
        int len = snprintf(buffer.getCur(), fMaxIntegerSize, "%.12g", data);
        buffer.add(len);
    }
    return *this;
}
Logstream& Logstream::operator<<(double data){
    if (buffer.getLeft() >= fMaxIntegerSize) {
        int len = snprintf(buffer.getCur(), fMaxIntegerSize, "%.12g", data);
        buffer.add(len);
    }
    return *this;
}

Logstream& Logstream::operator<<(unsigned long long data){
    formatInteger(data);
    return *this;
}
Logstream& Logstream::operator<<(long double data){
    if (buffer.getLeft() >= fMaxIntegerSize) {
        int len = snprintf(buffer.getCur(), fMaxIntegerSize, "%.12g", data);
        buffer.add(len);
    }
    return *this;
}
Logstream& Logstream::operator<<(char c){
    buffer.append(&c, 1);
    return *this;
}
Logstream& Logstream::operator<<(const char* data){
    if(data == nullptr){
        return *this << "(null)";
    }
    buffer.append(data, strlen(data) + 1);
    return *this;
}
Logstream& Logstream::operator<<(const unsigned char* str){
    return operator<<(reinterpret_cast<const char*>(str));
}
Logstream& Logstream::operator<<(const std::string& str){
    buffer.append(str.c_str(), str.size());
    return *this;
}
