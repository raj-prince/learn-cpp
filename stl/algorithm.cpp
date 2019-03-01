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

    vector<int> sorted_v = {2, 5, 6, 8, 10, 13};

    // cnt value b/w [3, 6]
    vector<int>::iterator lower_it = lower_bound(sorted_v.begin(), sorted_v.end(), 3); // return first value equal or greater than 3
    vector<int>::iterator upper_it = upper_bound(sorted_v.begin(), sorted_v.end(), 6); // returns first value greater than 6
    int cnt = distance(lower_it, upper_it);
    cout << "Count: " << cnt << endl;
    return 0;
}