#include <iostream>
#include <queue>

using namespace std;


int main() {
    priority_queue<int> max_pq; // default max on the top.
    max_pq.emplace(3);
    max_pq.emplace(4);
    max_pq.emplace(5);
    max_pq.emplace(1);
    max_pq.emplace(2);
    while (!max_pq.empty()) {
        int top = max_pq.top();
        max_pq.pop();
        cout << top << endl;
    }
    auto comp = [](int a, int b) {
        return a > b;
    };
    priority_queue<int, vector<int>, decltype(comp)> min_pq(comp); // with own comparato;
    min_pq.emplace(3);
    min_pq.emplace(4);
    min_pq.emplace(5);
    min_pq.emplace(1);
    min_pq.emplace(2);
    while (!min_pq.empty()) {
        int top = min_pq.top();
        min_pq.pop();
        cout << top << endl;
    }
}