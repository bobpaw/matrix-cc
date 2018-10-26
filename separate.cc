#include <iostream>
#include <string>
#include "separate.h"

int main () {
	std::string line;
	try {
		while (true) {
			std::cout << "> " << std::flush;
			std::getline(std::cin, line);
			if (line.size() == 0 || std::string("exit").find(line) == 0 || std::string("quit").find(line) == 0) break;
			auto a = separate::remove(separate::split(line, ","), ", ");
			for (auto i : a) std::cout << i << std::endl;
		}
	} catch (const char *e) {
	  std::cerr << e << std::endl;
	  return -1;
	}
	if (std::cin.eof()) std::cout << std::endl << std::flush;
	return 0;
}
