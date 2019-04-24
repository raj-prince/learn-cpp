#include <iostream>

using namespace std;

/**
 * Things to Remember:
 * 
 * 1. auto type deduction is usually the same as template type deduction, but auto type deduction
 *    assumes that a braced initializer represents a std::initializer_list, and template type deduction doesn't.
 * 
 * 2. auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
 **/


// Think auto like below template to deduce type of auto.
auto x = 23;
template <typename T>
void f1(T param);

const auto cx = x;
template <typename T>
void f2(const T param);

const auto& rx = cx;
template <typename T>
void f3(const T& param);

// auto as an function return type.
auto createInitList() {
    // return {1, 2, 3}; // this will give a compiler error, because auto is deduced like template.
    return x;
}

// auto as an lambda parameter.
auto test = [](const auto& new_val) {
    cout << new_val << endl;
};

int main() {
    // test({1, 2, 3}); won't compile because, it is deduced like template.
    test(4);
}