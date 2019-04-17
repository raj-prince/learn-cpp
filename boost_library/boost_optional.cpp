#include <iostream>
#include<boost/optional.hpp>
#include<boost/optional/optional_io.hpp>

using namespace std;

// Installation: sudo apt install libboost-dev; sudo apt install libboost-all-dev
// Reference: https://www.osetc.com/en/how-to-install-boost-on-ubuntu-16-04-18-04-linux.html#install-boost-ppa

boost::optional<int> ok(int x) {
    if (x % 2 == 0) {
        return boost::none;
    } else {
        return x;
    }
}

inline int val(boost::optional<int> x) {
    int z = 10;
    if (x) {
        z = x.get();
    }
    return z;
}

int main() {
    if (ok(2) == boost::none) {
        cout << "Working fine" << endl;
    }

    cout << val(boost::optional<int>(4)) << endl;
    cout << val(boost::none) << endl;

    cout << ok(2) << endl;
    cout << ok(3) << endl;
    return 0;
}