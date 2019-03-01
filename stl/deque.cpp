#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> dq;

    cout << dq.emplace_back(1) << endl; // add 1 at last, return 1.
    cout << dq.emplace_front(2) << endl; // add 2 at first, return 2.
    cout << dq.size() << endl; // 2.
    cout << dq.front() << endl; // return 2
    cout << dq.back() << endl; // return 1
    dq.pop_back(); // delete 1
    dq.pop_front(); // delete 2
    cout << dq.size() << endl; // 0.

    // generally dq is like vector which grows at both the end.
    // it is implemented using dynamic array, memory might not be contiguous in case of dq.

    return 0;

}