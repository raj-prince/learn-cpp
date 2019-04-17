#include <iostream>
#include <functional>
#include <future>

using namespace std;

typedef function<int(int, int)>  bi_function_type;

void execute_function(int a, int b, const bi_function_type& fun) {
    cout << fun(a, b) << endl;
}

inline int sub(int a, int b) {
    return a - b;
}

inline int mul(int a, int b) {
    return a * b;
}

inline void add(promise<int>&& p, int a, int b) {
    p.set_value(a + b);
}

// checks a future object have the result available.
template<typename R>
bool is_ready(future<R> const& f) {
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}


int main() {
    execute_function(2, 3, sub);
    execute_function(2, 3, mul);

    // to set a int value or exception or notification
    promise<int> p_addition;
    
    // get the promise return
    future<int> f_addition = p_addition.get_future();
    if (is_ready(f_addition)) {
        cout << f_addition.get() << endl;
    } else {
        cout << "Future is not ready now." << endl;
    }
    // calculate the promise in different thread.
    thread exec(add, move(p_addition), 2, 3);

    // now get the result.
    cout << f_addition.get() << endl;

    exec.join();
    return 0;
}