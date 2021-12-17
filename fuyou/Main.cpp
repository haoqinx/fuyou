#include <iostream>
#include "EventLoop.h"
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
    test sss(10);
    func(std::move(sss));
    cout << "???";
    return 0;
}