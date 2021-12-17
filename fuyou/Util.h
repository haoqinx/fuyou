#ifndef _UTIL_H
#define _UTIL_H
#include <string>
#include <unistd.h>
#include <errno.h>
namespace fuyou
{
void shutdownWrite(int fd);
ssize_t writen(int fd, void* buff, size_t n);
ssize_t readn(int fd, void *buff, size_t n);

} // namespace fuyou


#endif