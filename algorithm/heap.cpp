#include <iostream>
#include <vector>

using namespace std;

template <class T>
class HEAP {
    vector<T> v;

public:
    HEAP() {} // default constructor.

    HEAP(const vector<T>& _v) {
        v = _v;
    } // parameterized constructor.

    // delete and return max element from the heap.
    int pop() {
        int sz = get_size();
        if (sz >= 0) {
            int x = v[0];
            swap(v[0], v[sz - 1]);
            v.pop_back();
            push_down(0);
            return x;   
        }
        return -1;
    }

    // need to heappify from the last internal node to root.
    void make_heap() {
        int sz = get_size();
        for (int i = (sz - 1) / 2; i >= 0; i--) {
            push_down(i);
        }
    }

    // just push small element down.
    void push_down(int i) {
        int max_c = get_max_child(i);
        if (max_c != i && v[max_c] > v[i]) {
            swap(v[max_c], v[i]);
            push_down(max_c);
        }
    }

    // push big element at the top.
    void push_up(int i) {
        int mx_c = get_max_child(i);
        if (v[i] < v[mx_c]) {
            swap(v[i], v[mx_c]);
        }
        if (i > 0) {
            int p = (i - 1) >> 1;
            push_up(p);
        }
    }

    // return the size of the heap.
    int get_size() {
        int sz = static_cast<int>(v.size());
        return sz;
    }

    // return index of max child node.
    // same in case of leaf node.
    int get_max_child(int i) {
        int l = (i << 1) + 1;
        int r = (i << 1) + 2;
        int sz = get_size();
        if (l >= sz && r >= sz) {
            return i;
        }
        if (l >= sz) {
            return r;
        }
        if (r >= sz) {
            return l;
        }
        int mx = l;
        if (v[mx] < v[r]) {
            mx = r;
        }
        return mx;
    }

};

int main() {
    vector<int> x = {1, 8, 4, 3, 9};
    HEAP<int> heap(x);
    heap.make_heap();
    int sz_x = static_cast<int>(x.size());
    for (int i = 0; i < sz_x; i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << heap.pop();
    }
    return 0;
    
}
