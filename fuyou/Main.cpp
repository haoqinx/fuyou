#include <iostream>
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "EventLoopThreadPool.h"
#include "Server.h"
using namespace fuyou;
using namespace std;
class test{
public:
    int a;
    test(int a):a(a){}
    ~test(){
        cout << "del" << endl;
    }
};
void func(test&& t){
    cout << "func " << t.a << endl;
}
int main(){
    EventLoop loop;
    Server server(&loop, 4, 6666);
    server.start();
    loop.loop();
}