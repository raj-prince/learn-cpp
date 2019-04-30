#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;

/**
 *  Things to remember:
 *  1. Invisible proxy types can cause auto to deduce the wrong type for an initializing expression.
 *  2. The explicitly typed initializer idiom forces auto to deduce the type you want it to have.
 * 
 * Here in the below example, vector<bool>::reference is a proxy type for the bool.
 * */

std::vector<bool> func() {
    vector<bool> res;
    res.emplace_back(true);
    res.emplace_back(false);
    return res;
}

int main() {
    // auto test = func()[2];
    // The above will show unexpected behavior, because type deduction will be std::__1::__bit_reference<std::__1::vector<bool, std::__1::allocator<bool> >, true>
    // function will return reference of temporary vector<bool> res, after destruction, it will show undefined behavior.
    bool test = func()[2];
    using boost::typeindex::type_id_with_cvr;
    cout << "test type is = " << type_id_with_cvr<decltype(test)>().pretty_name() << endl;
    return 0;
}