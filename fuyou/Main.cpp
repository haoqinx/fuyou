#include <iostream>
#include "net/EventLoop.h"
#include "net/EventLoopThread.h"
#include "net/EventLoopThreadPool.h"
#include "net/Server.h"
using namespace fuyou;
using namespace std;
int main(){
    EventLoop loop;
    Server server(&loop, 4, 6666);
    server.start();
    loop.loop();
}
