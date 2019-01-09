/*******************************************************************************
* Name : gcd.cpp
* Author : Bobby Georgiou
* Date : 08/31/2018
* Description : Lab 1 - GCD
* Pledge : "I pledge my honor that I have abided by the Stevens Honor System."
******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int gcd_iterative(int m, int n) {
	m = abs(m); n = abs(n);
	if (m == n) { return m; }
	if (m == 0 || n == 0) { return 1; }
	int m1, n1;
	if (n > m) {
		m1 = n; n1 = m;
	} else {
		m1 = m; n1 = n;
	}
	while (m1 % n1 != 0) {
		int mtemp = m1;
		m1 = n1;
		n1 = mtemp % n1;
	}
	return n1;
}

int gcd_recursive(int m, int n) {
	m = abs(m); n = abs(n);
	if (m == n) { return m; }
	if (m == 0 || n == 0) { return 1; }
	if (n > m) {
		int mtemp = m; m = n; n = mtemp;
	}
	if (m % n == 0) {
		return n;
	}
	return gcd_recursive(n, m % n);
}

int main(int argc, char *argv[]) {
	int m, n;
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> m)) {
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if (!(iss >> n)) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) << endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) << endl;
	return 0;
}
