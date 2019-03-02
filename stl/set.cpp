#include <iostream>
#include <set>

using namespace std;

void print(const set<int>& s) {
    for(int x: s) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    multiset<int> ms; // same as set, but can store deuplicate key.
    set<int> s;

    pair<set<int>::iterator, bool> r = s.emplace(4);
    cout << *(r.first) << " " << r.second << endl; // 4 and true (insertion successful).
    r = s.emplace(4);
    cout << *(r.first) << " " << r.second << endl; // 4 and false (not inserted already exist).
    s.emplace(5);
    s.emplace(3);
    s.emplace(6);
    s.emplace(8);
    print(s); // 3, 4, 5, 6, 8
    cout << s.count(10) << endl; // 0
    cout << s.count(8) << endl; // 1
    cout << s.erase(10) << endl; // 0: no. of element erased.
    cout << s.erase(8) << endl; // 1: no. of element erased.
    set<int>::iterator it = s.find(10);
    if (it != s.cend()) { // segmentation fault otherwise.
        s.erase(it);
    }
    set<int>::iterator low = s.lower_bound(3);
    set<int>::iterator up = s.upper_bound(5);
    it = s.erase(low, up); // return iterator of next to deleted element.

}