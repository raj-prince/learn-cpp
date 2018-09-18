#include <iostream>

using namespace std;

// function is called by matching the, return type, name, and argument.

// returns the volume of a cube.
double volume(double a) {
	cout << "Returning the volume of cube." << endl;
	return a * a * a;
}

// return volume of a cylinder.
double volume(double r, double h) {
	const static double _pi = 3.14;
	cout << "Returnning volume of the cylinder." << endl;
	return _pi * r * r * h;
}

// return volume of cuboid.
double volume(double a, double b, double c) {
	cout << "Returnnig volume of the cuboid." << endl;
	return a * b * c;
}

int main() {
	cout << volume(2.0) << endl;
	cout << volume(2.0, 2.0) << endl;
	cout << volume(2.0, 3.0, 4.0) << endl;
	return 0;
}