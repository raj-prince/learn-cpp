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

    vector<int> heap_v = {3, 6, 7, 9, 4};
    // check, is this vector hippified.
    if (!is_heap(heap_v.begin(), heap_v.end())) {
        make_heap(heap_v.begin(), heap_v.end());
    }
    for_each(heap_v.begin(), heap_v.end(), [](int x) {
        cout << x << " ";
    });

}