#include <iostream>
#include <cstdarg>

using namespace std;

// Technique to take variable number of argument.
// Example, using how printf is implemented interanlly.

// takes count as well as all the elements.
// and returns the averaget of all the elements.
double average(const int count, ...) {
	va_list ap;
	double total = 0.0;

	// enable access to all the variable arguments, followed by count.
	va_start(ap, count);
	for (int i = 0; i < count; ++i) {
		//  enables access to next variadic function arguments 
		total += va_arg(ap, double);
	}
	// clean-up of va_list object.
	va_end(ap);
	return total / count;
}

// works like printf, format plus args
int message(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int rc = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return rc;
}

int main() {
	message("This is a message.");
	message("Average: %lf", average(5, 2.0, 5.0, 8.0, 9.0, 0.0));
	return 0;
}