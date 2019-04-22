#include <iostream>
#include <boost/type_index.hpp>

using namespace std;

/**
 * :: Template Type Deduction
 * 
 * Case 1: ParamType is a Reference or Pointer (*, &) but not a Universal Reference.
 *   - If expr's type is a reference, ignore the reference part.
 *   - Then pattern-match expr's type against ParamType to determine T.
 * 
 * Case 2: ParamType is a Universal Pointer (&&).
 *   - If expr is an lvalue both T and ParamType are deduced to be lvalue references. Then both T
 *     and ParamType will be an lvalue reference.
 *   - If expr is an rvalue, the "normal" (i.e., Case 1) will be applied.
 * 
 * Case 3: ParamType is Neither a Pointer nor a Reference.
 *   - As before, if expr's type is a reference, ignore the reference part.
 *   - After ignoring expr's reference-ness, expr is const, ignore that too. 
 * 
 * Things to Remember:
 *   - During template type deduction, arguments that are references are treated as
 *     non-references, i.e. their reference-ness is ignored.
 *   - When deducing types for universal reference parameters, lvalue arguments get
 *     special treatment.
 *   - When deducing types for by-value parameters, const and or volatile arguments
 *     are treated as non-const and non-volatile.
 *   - During template type deduction, arguments that are array or function names decay
 *     to pointers, unless they're used to initialize references.
 * */

template <typename T>
void f1(const T& param) {
    using boost::typeindex::type_id_with_cvr;
    cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "ParamType = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

template <typename T>
void f2(T&& param) {
    using boost::typeindex::type_id_with_cvr;
    cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "ParamType = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

template <typename T>
void f3(T param) {
    using boost::typeindex::type_id_with_cvr;
    cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "ParamType = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

// return size of an array as a compile-time constant.
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&) [N]) {
    return N;
}

void func(int x, double y) {
    cout << x << " " << y << endl;
}

int main() {
    int x = 25;
    const int cx = x;
    const int& rx = x;
    const char name[] = "prince";
    const char* ptrToName = "prince";
    array<char, arraySize(name)> testName; // array of length of (array name).

    // here type of x is an expression.

    f1(x); // int, int const&
    f1(cx); // int, int const&
    f1(rx); // int, int const&
    f1(name); // char [7], char const (&) [7]
    f1(ptrToName); // char const*, char const* const&
    f1(func); // void (int, double), void (&)(int, double)

    f2(x); // int&, int&
    f2(cx); // int const&, int const&
    f2(rx); // int const&, int const&
    f2(name); // char const (&) [7], char const (&) [7] (so we can use this to get number of elements.)
    f2(ptrToName); // char const*&, char const*&
    f2(func); // void (&) (int, double), void (&) (int, double)

    f3(x); // int, int
    f3(cx); // int, int
    f3(rx); // int, int
    f3(name); // char const*, char const*
    f3(ptrToName); // char const*, char const*
    f3(func); // void (*)(int, double), void (*)(int, double)

    return 0;
}