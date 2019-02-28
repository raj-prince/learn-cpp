#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class KMP {
    // back table.
    // b[i]: stores len of longest proper prefix-suffix of string[0, i - 1],
    vector <int> b;

public:
    void make_b(const string& pattern) {
        int _size = static_cast<int>(pattern.size());
        b = vector<int>(_size + 1, 0);
        b[0] = -1;
        int i = 0, j = -1;
        while (i < _size) {
            while (j >= 0 && pattern[i] != pattern[j]) {
                j = b[j];
            }
            i++;
            j++;
            b[i] = j;
        }
    }

    void print_b() {
        int _size = static_cast<int>(b.size());
        for (int i = 0; i < _size; i++) {
            if (i > 0) {
                printf(" ");
            }
            printf("%d", b[i]);
        }
        printf("\n");
    }

    void match(const string& text, const string& pattern) {
        make_b(pattern);
        print_b();
        int text_size = static_cast<int>(text.size());
        int pattern_size = static_cast<int>(pattern.size());
        int i = 0, j = 0;
        while (i < text_size) {
            while (j >= 0 && text[i] != pattern[j]) {
                j = b[j];
            }
            i++;
            j++;
            if (j == pattern_size) {
                printf("Matched at: %d\n", i - pattern_size);
                j = b[j];
            }
        }
    }

    // S = (AAAA) then return A.
    string recurring_string(const string& s) {
        make_b(s);
        print_b();
        int _size = static_cast<int>(s.size());
        int len = b[_size];
        int a_len = _size - len;
        return s.substr(0, a_len);
    }

    void clear() {
        b.clear();
    }
};


int main() {
    int test;
    cin >> test;
    while (test--) {
        KMP kmp;
        string s;
        cin >> s;
        cout << kmp.recurring_string(s) << endl;
    }
    return 0;
}