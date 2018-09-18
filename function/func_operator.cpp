#include <iostream>

using namespace std;

// Using this example we can overload any operator
// to work on Object.

class A {

	int a;

public:

	A(const int &a) : a(a) {}
	const int & value() const { 
		return a;
	}
};

int operator + (const A &lhs, const A &rhs) {
	puts("operator + for class A");
	return lhs.value() + rhs.value();
}

int main(int argc, char **argv) {
	A a(7);
	A b(42);
	printf("add! %d\n", a + b);
	return 0;
}