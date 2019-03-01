#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<int> q;

    cout << q.empty() << endl; // true;
    cout << q.emplace(2) << endl; // will return 2.
    cout << q.emplace(3) << endl; // will return 3.
    cout << q.size() << endl; // 2
    cout << q.front() << endl; // 2
    q.pop(); // remove 2
    cout << q.front() << endl; // 3
    q.pop(); // remove 3
    cout << q.size() << endl; // 0
}