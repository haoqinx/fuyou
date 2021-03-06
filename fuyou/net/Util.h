#ifndef _UTIL_H
#define _UTIL_H
#include <string>
#include <unistd.h>
#include <errno.h>
#include "../base/Logger.h"
namespace fuyou
{
void shutdownWrite(int fd);
ssize_t writen(int fd, void* buff, size_t n);
ssize_t readn(int fd, void *buff, size_t n);

ssize_t writen(int fd, std::string& buf);
ssize_t readn(int fd, std::string& buf, bool& zero);
int socket_bind_listen(int port);
void handle_for_sigpipe();
int setSocketNonBlocking(int fd);
//禁用 Nagle’s Algorithm
void setSocketNodelay(int fd);
} // namespace fuyou


#endif