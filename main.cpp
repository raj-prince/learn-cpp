#include <iostream>
#include <functional>
#include <thread>
#include <vector>

using namespace std;

void E(int& a, int& b) {
    cout << a + b << endl;
}

void E(int&& a, int&& b) {
    cout << a + b << endl;
}

template<typename T>
void f(T&& a, T&& b) {
    E(forward<T>(a), forward<T>(b));
}


class test{
    public:
    int a = 0;
    void constMethod(int& b) const{
        // a = 6;
        b = 9;
    }
};

int main() {
    test e;
    int a = 10;
    e.constMethod(a);
    return 0;
}