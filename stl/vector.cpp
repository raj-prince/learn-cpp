#include <iostream>
#include <vector>

using namespace std;


int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        cout << "Iteration No: " << i << endl;
        v.push_back(i);
        cout << "Size: " << v.size() << endl;
        // how much element can push_back without growing.
        // will grow after 1, 2, 4, 8...;
        cout << "Capacity: " << v.capacity() << endl;
    }

    // but we can fix the reserve capacity.
    vector<int> new_v;
    new_v.reserve(10);
    for (int i = 0; i < 11; i++) {
        cout << "Iteration No: " << i << endl;
        new_v.push_back(i);
        cout << "Size: " << new_v.size() << endl;
        // will not grow till the size 10.
        // capacity will 20 when we will push 11th element.
        cout << "Capacity: " << new_v.capacity() << endl;
    }

    // assign: assign new contents and modify the size accordingly.
    new_v.assign(v.begin(), v.end());
    for (int x: new_v) {
        cout << x << endl;
    }

    // clear: removes all elements from the vector.
    v.clear();
    cout << "After clear vector v..." << endl;
    // will print nothing.
    for (int x: v) {
        cout << x << endl;
    }

    // erase: removes either one element (position) or
    // range of elements [first, last)
    new_v.erase(new_v.begin() + 5); // erase 6th element
    new_v.erase(new_v.begin(), new_v.begin() + 5); // erase element [0, 5)
    // use emplace_back instread of push_bacl and emplace instread of insert
    // because no intermediate copy happens in emplace and emplace_back
    new_v.emplace_back(4);
    new_v.emplace(new_v.begin(), 780);
    for (int x: new_v) {
        cout << x << endl;
    }
    // traversal using iterator
    vector<int>::iterator it = new_v.begin();
    while (it != new_v.end()) {
        cout << *it << endl;
        it++; // also possible it += 2
    }
    // traversal using auto loop
    for (auto x: new_v) {
        cout << x << endl;
    }

    // Also we can use cbegin(), cend(), crbegin(), crend();
    // which return const iterator.
    vector<int>::const_reverse_iterator it_r = new_v.crbegin();
    while (it_r != new_v.crend()) {
        cout << *it_r << endl;
        ++it_r;
    }
}
