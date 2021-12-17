#include "Util.h"
#include <sys/socket.h>

namespace fuyou
{

void shutdownWrite(int fd){
    shutdown(fd, SHUT_WR);
}
} // namespace fuyou
