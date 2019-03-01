#include <iostream>
#include <memory>
#include <vector>
#include <cstring>

using namespace std;

constexpr int ALPHA = 26;

struct Node {
    int cnt;
    int end_cnt;
    shared_ptr<Node> child[ALPHA];

    Node(int _cnt = 0, int _end_cnt = 0) {
        cnt = _cnt;
        end_cnt = _end_cnt;
        for (int i = 0; i < ALPHA; i++) {
            child[i] = nullptr;
        }
    }
};

class Trie {
    shared_ptr<Node> root;

public:

    Trie() {
        root = make_shared<Node>(-1);
    } // constructor.

    ~Trie() {
        root.reset();
    } // destructor.

    // add string in the trie.
    void add(const string& s) {
        shared_ptr<Node> crawler = root;
        for (char c: s) {
            int idx = ind(c);
            if (crawler->child[idx] == nullptr) {
                crawler->child[idx] = make_shared<Node>(0);
            }
            crawler = crawler->child[idx];
            crawler->cnt++;
        }
        crawler->end_cnt++;
    }

    // soft_delete.
    void del(const string& s) {
        shared_ptr<Node> crawler = root;
        bool exist = true;
        for (char c: s) {
            int idx = ind(c);
            if (crawler->child[idx] != nullptr) {
                crawler = crawler->child[idx];
                crawler->cnt--;
            } else {
                exist = false;
                break;
            }
        }
        if (exist) {
            crawler->end_cnt--;
        }
    }

    // check existence of the string.
    bool check(const string& s) {
        shared_ptr<Node> crawler = root;
        for (char c: s) {
            int idx = ind(c);
            if (crawler->child[idx] == nullptr) {
                crawler->child[idx] = make_shared<Node>(0);
            }
            crawler = crawler->child[idx];
        }
        return (crawler->end_cnt > 0);
    }

    inline int ind(char c) {
        return static_cast<int>(c - 'a');
    }
};

int main() {
    vector<string> vs = {"prince", "raj", "kumar", "kumar"};
    Trie trie;
    for (string s: vs) {
        trie.add(s);
    }
    cout << trie.check("prince") << endl; // true.
    cout << trie.check("kumar") << endl; // true.
    trie.del("kumar");
    cout << trie.check("kumar") << endl; // true.
    trie.del("kumar");
    cout << trie.check("kumar") << endl; // false.
    cout << trie.check("kfjlsjf") << endl; // false.
    return 0;
}