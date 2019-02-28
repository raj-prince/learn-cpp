#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {2, 4, 6, 8};
    // return true, if the pred function will true for all the element.
    bool all_even = all_of(v.begin(), v.end(), [](int i) {
        return i % 2 == 0;
    });
    if (all_even) {
        cout << "All elements are even." << endl;
    } else {
        cout << "Not all elements are even." << endl;
    }

    // return true, if the pred return true for any of them.
    bool any_even = any_of(v.begin(), v.end(), [](int i) {
        return i % 2 == 0;
    });
}