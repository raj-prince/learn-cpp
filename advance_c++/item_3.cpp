#include <iostream>
#include <deque>

using namespace std;

/**
 * 1. decltype almost always yields the type of a variable or expression without any modifications.
 * 2. For lvalue expressions of type T other than names, decltype always reports a type of T&.
 * 3. C++14 supports decltype(auto) which, like auto, deduces a type from its initializer, but
 *    it performs the type deduction using the decltype rules.
 **/

// use as function return type.
// auto specifies that the type is to be deduced, and decltype says that decltype rules should be
// used during the decuction.
template <typename Container, typename Index>
decltype(auto) authAndAccess(Container& c, Index i) { // only auto won't compile because return type will be int. (not int&) as returned by container.
    return c[i];
}

int main() {
    std::deque<int> dq;

    authAndAccess(dq, 5) = 10;

    // also used to declare variable.
    int x;
    const int& cx = x;
    auto x1 = cx; // auto type deduction, and type will be int.

    decltype(auto) x2 = cx; // decltype type deduction, ie. const int&

    return 0;
}