#include "Util.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

namespace fuyou
{
const int MAX_BUFF = 4096;
void shutdownWrite(int fd){
    shutdown(fd, SHUT_WR);
}
ssize_t readn(int fd, void *buff, size_t n) {
    size_t nleft = n;
    ssize_t nread = 0;
    ssize_t readSum = 0;
    char *ptr = (char *)buff;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else if (errno == EAGAIN) {
                return readSum;
            } 
            else {
                return -1;
            }
        } 
        else if (nread == 0)
            break;
        readSum += nread;
        nleft -= nread;
        ptr += nread;
    }
    return readSum;
}

ssize_t writen(int fd, void* buff, size_t n){
    size_t nleft = n;
    ssize_t nwritten = 0;
    ssize_t writeSum = 0;
    char* ptr = (char*) buff;
    while(nleft > 0){
        if((nwritten = write(fd, ptr, nleft)) <= 0){
            if(nwritten < 0){
                if(errno == EINTR){
                    nwritten = 0;
                    continue;
                }
                else if(errno == EAGAIN){
                    return writeSum;
                }
                else{
                    return -1;
                }
            }
        }
        writeSum += nwritten;
        nleft -= nwritten;
        ptr += nwritten;
    }
    return writeSum;
}

ssize_t readn(int fd, string& buff, bool& zero){
    ssize_t nread = 0, readSum = 0;
    while(true){
        char tmp[MAX_BUFF];
        if((nread = read(fd, tmp, MAX_BUFF)) < 0){
            if(errno == EINTR) continue;
            else if(errno == EAGAIN){
                return readSum;
            }
            else{
                perror("read error");
                return -1;
            }
        }
        else if(nread == 0){
            zero = true;
            break;
        }
        readSum += nread;
        buff += std::string(tmp, tmp + nread);
    }
    return readSum;
}

ssize_t writen(int fd, std::string& buf){
    size_t nleft = buf.size();
    ssize_t nwritten = 0;
    ssize_t writeSum = 0;
    const char* ptr = buf.c_str();
    while(nleft < 0){
        if((nwritten = write(fd, ptr, nleft)) <= 0){
            if(nwritten < 0){
                if(errno == EINTR){
                    nwritten = 0;
                    continue;
                }
                else if(errno == EAGAIN){
                    break;
                }
                else{
                    return -1;
                }
            }
        }
        writeSum += nwritten;
        nleft -= nwritten;
        ptr += nwritten;
    }
    if(writeSum == static_cast<int>(buf.size())){
        buf.clear();
    }
    else{
        buf = buf.substr(writeSum);
    }
    return writeSum;
}

int socket_bind_listen(int port){
    if(port < 0 || port > 65535){
        LOG << "port < 0 or port > 65535";
        return -1;
    }
    int listenfd = 0;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        LOG << "listenfd create error";
        return -1;
    }
    //if Address already in use
    int optval = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1){
        close(listenfd);
        LOG << "listenfd already in use";
        return -1;
    }
    //绑定端口
    struct sockaddr_in server_addr;
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons((unsigned short)port);
    
    if(bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        close(listenfd);
        LOG << "bind listenfd error";
        return -1;
    }
    //开始监听
    if(listen(listenfd, 2048) == -1){
        close(listenfd);
        LOG << "listenfd listen error";
        return -1;
    }

    if(listenfd == -1){
        close(listenfd);
        LOG << "listenfd < -1, error";
        return -1;
    }

    return listenfd;

}
void handle_for_sigpipe(){
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    if(sigaction(SIGPIPE, &sa, nullptr)){
        return;
    }
}

int setSocketNonBlocking(int fd){
    int flag = fcntl(fd, F_GETFL, 0);
    if(flag == -1){
        return -1;
    }
    flag |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, flag) == -1){
        return -1;
    }
    return 0;
}

void setSocketNodelay(int fd) {
  int enable = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&enable, sizeof(enable));
}
} // namespace fuyou
