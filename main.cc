#include <iostream>
#include <string>
#include "matrix.h"

int main () {
	try {
		auto a = matrix::I(2);
		auto b = matrix::O(3);
		auto c = matrix::Matrix<>({{2, 3, 0, 4},{2, 3, 1, -1},{4, 7, 1, 2},{3, 5, 3, 0}});
		std::cout << a << std::endl;
		std::cout << std::string(b) << std::endl;
		std::cout << c << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}
