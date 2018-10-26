#include <iostream>
#include <string>
#include "matrix.h"

int main () {
	try {
		auto c = matrix::Matrix<>({{2, 3, 0, 4},{2, 3, 1, -1},{4, 7, 1, 2},{3, 5, 3, 0}});
		auto a = matrix::I(c.rows());
		std::cout << c << std::endl;
		std::cout << a << std::endl;
		std::cout << c * a << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}
