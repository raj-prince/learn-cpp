#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;

/**
 * 
 * 1. auto variables must be initialized, are generally immune to type mimsmatches that can lead
 *    to portability or efficiency problems, can ease the process of refactoring, and typically 
 *    require less typing than variables with explicitly specified types.
 * 
 **/

// portability issue
vector<int> v;
unsigned sz = v.size(); // unsigned will be different for different system., so might cause a problem

// space efficiency
// take more memory than auto declared object.
std::function<int(int, int)> add = [](int a, int b) {
    return a + b;
};
 
// correct way
auto add_via_lambda = [](int a, int b) -> int {
    return a + b;
};



int main() {
    // Efficiency issue.
    // key part of unordered_map is a const
    // a new object of pair wiill be created to bind with p.
    unordered_map<string, int> m;
    for (const pair<string, int>& p: m) { // it should be (const string instread of string)
        cout << p.first << " " << p.second << endl;
    }
    // correct way
    for (const auto& p: m) {
        cout << p.first << " " << p.second << endl;
    }
    cout << add(3, 4) << endl;
    cout << add_via_lambda(4, 5) << endl;
}