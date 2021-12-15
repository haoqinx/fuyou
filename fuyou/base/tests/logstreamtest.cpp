#include "../Logstream.h"
#include <iostream>
using namespace std;
int main(){
    fuyou::Logstream s;
    const char* c = "this is a test";
    s << c << c;
    cout << s.getinfo() << endl;
    for(int i = 0; i < 1024; ++i){
        cout << (char)*(s.getinfo() + i); 
    }
    return 0;
}