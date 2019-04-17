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

int main() {
    int i = 0, j = 1;
    f(i, j);
    f(0,stdj);
    return 0;
}