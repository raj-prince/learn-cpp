#include <iostream>
#include <bitset>

using namespace std;

constexpr int SZ = 64;

int main() {
    bitset<SZ> a;
    cout << a << endl;

    a[0] = 1; // set 0th bit
    a[2] = 1; // set 2nd bit

    cout << a << endl;

    cout << "One: " << a.count() << endl;
    cout << "Zero: " << a.size() - a.count() << endl;


    a.set(3);
    cout << a << endl;
    a.reset(3);
    cout << a << endl;
    a.flip(3);
    cout << a << endl;
    a.flip();
    cout << a << endl;

    unsigned long long x = a.to_ullong();
    cout << x << endl;
    string x_s = a.to_string();
    cout << x_s << endl;
    return 0;
}