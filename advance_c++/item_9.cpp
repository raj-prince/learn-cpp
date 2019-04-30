#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;


/**
 *  Things to Remember
 *  1. typedefs don't support templatization, but alias declarations do.
 *  2. Alias templates avoid the '::type' suffix and, in templates the "typename" prefix often required to refer to typedefs.
 *  3. C++14 offers alias templates fro all the C++11 type traits transformation.
 * */

// FP is a synonym for a pointer to a function taking an int and a const string& and returning nothing.
typedef void (*FP)(int, const string&);
using FP = void (*)(int, const string&);

void execute(FP x) {
    x(2, "prince");
}

void Test(int a, const string& b) {
    cout << a << " " << b << endl;
}

class Point {
    public:
    int x, y;
};

class Wine {

};

template<typename T>
using MyAllocListAlias = list<T, allocator<T>>;

template<typename T>
struct MyAllocList {
    typedef list<T, allocator<T>> type;
};

template<typename T>
class Declaretypedef {
    private:
        MyAllocList<T>::type my_list; // dependent type name 'MyAllocList<T>::type' typname required otherwise won't compile.
        MyAllocListAlias<T> my_aliased_list;
};

// specialization of MyAllocList template
template<>
class MyAllocList<Wine> {
    private:
        enum class WineType {
            White,
            Red,
            Yello
        };

    WineType type; // typename used to avoid the confusion.
};

// type traits in c++11 to play with T inside template method or class.
// remove_const<T>::type -> yields T from const T
// remove_reference<T>::type -> yields T from T& and T&&
// add_lvalue_reference<T>::type -> yields T& from T
// in c++ 14
// remove_const_t<T> -> yields T from const T
// remove_reference_t<T>-> yields T from T& and T&&
// add_lvalue_reference_t<T> -> yields T& from T

// Transformation
// using remove_const_t = typename remove_const<T>::type;

int main() {
    execute(Test);
    MyAllocListAlias<Point> mp;
    MyAllocList<Point>::type mp1;
    Point p1;
    mp.push_front(p1);
    mp1.push_front(p1);
    for (auto p: mp) {
        cout << p.x << " " << p.y << endl;
    }
    for (auto p: mp1) {
        cout << p.x << " " << p.y << endl;
    }
    return 0;
}