#include <iostream>
#include <map>

using namespace std;

template <typename A, typename B>
void print(const map<A, B>& m) {
    for (auto x: m) {
        cout << "Key: " << x.first << " Value: " << x.second << endl;
    }
}

int main() {
    // works same as map, but can contain duplicate
    // also it doesn't give support for this operator.
    multimap<int, int> mm; // mm[0] is not valid.
    
    map<int, int> m;
    pair<map<int, int>::iterator, bool> t = m.emplace(3, 4); // iterator and successfully inserted or not.
    
    cout << m[3] << endl; // 4.
    cout << m.count(3) << endl; // 1.
    cout << m.count(0) << endl; // 0.
    cout << m[0] << endl; // default value according to value type, and also insert 0 as key.
    cout << m.count(0) << endl; // 1.
    cout << (m.find(0) != m.cend()) << endl; // true.


    print<int, int>(m); // (0->0, 3->4);
    m.erase(0);
    print<int, int>(m); // (3->4);
    m.emplace(5, 10);
    m.emplace(4, 3); // (3->4, 4->3, 5->10)
    print<int, int>(m);
    map<int, int>:: iterator it = m.find(3);
    if (it != m.cend()) { // otherwise sigmentation fault.
        m.erase(it);
    }
    m.emplace(6, 23);
    m.emplace(1, 33);
    print<int, int>(m); // (1->33, 4->3, 5->10, 6->23);
    map<int, int>::iterator low = m.lower_bound(2);
    map<int, int>::iterator up = m.upper_bound(5);
    it = m.erase(low, up); // it points to next element, i.e., (6->23)
    print<int, int>(m); // (1->33, 6->23)

}