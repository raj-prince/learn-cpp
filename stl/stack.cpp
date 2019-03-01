#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> s;
    cout << s.empty() << endl; // true.
    cout << s.emplace(3) << endl; // push 3. return 3.
    cout << s.size() << endl; // 1
    cout << s.top() << endl; // just access top element.
    s.pop(); // remove top element.
    cout << s.size() << endl; // return 0.
}