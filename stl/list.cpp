#include <iostream>
#include <list>

using namespace std;

inline void print(const list<int>& l) {
    for (int x: l) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    list<int> l;
    
    l.emplace_back(5); // [5]
    l.emplace_back(6); // [5, 6]
    l.emplace_front(1); // [1, 5, 6]
    l.emplace_front(2); // [2, 1, 5, 6]
    print(l);
    l.pop_back(); // [2, 1, 5]
    l.pop_front(); // [1, 5]
    print(l);

    list<int>::iterator it = l.begin();
    // return an iterator that points to the newly emplaced element. i.e., at 23.
    l.emplace(it, 23); // [23, 1, 5]  (iterator points at 1)
    l.emplace(it, 24); // [23, 24, 1, 5] (iterator points at 1)
    print(l);
    advance(it, 1); // iterator points at 5
    // return iterator to the next element of deleted one.
    auto it1 = l.erase(it); // deleted 5 [23, 24, 1] (it1 points at l.end())
    print(l);
}