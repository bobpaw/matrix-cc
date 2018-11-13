#include "main.h"

int main () {
	std::string line;
	std::vector<std::string> lines;
	std::vector<std::vector<int>> hole;
	std::vector<matrix::Matrix<int>> matrices;
	std::string op;
	try {
		while (true) {
			std::cout << "> " << std::flush;
			std::getline(std::cin, line);
			if (line.size() == 0 || std::string("exit").find(line) == 0 || std::string("quit").find(line) == 0) break;
			if (line.find('*') != std::string::npos) {
				op = "*";
			} else if (line.find('+') != std::string::npos) {
				op = "+";
			}
			lines = separate::split(line, op);
			for (int i = 0; i < 2; ++i) {
			container::TextHolder b(lines[i], "[]");
			hole.clear();
			for (std::size_t i = 0; i < b.num(); i++) {
				auto a = separate::remove(separate::split(b[i].item(), ","), ", []");
				hole.push_back(std::vector<int>());
				for (auto item : a) hole[i].push_back(std::stoi(item));
			}
			std::cout << matrix::Matrix<int>(hole) << std::endl;
			matrices.push_back(matrix::Matrix<int>(hole));
			}
			if (op == "*") {
				std::cout << matrices[0] * matrices[1] << std::endl;
			} else if (op == "+") {
				std::cout << matrices[0] + matrices[1] << std::endl;
			}
		}
	} catch (const char *e) {
	  std::cerr << e << std::endl;
	  return -1;
	}
	if (std::cin.eof()) std::cout << std::endl << std::flush;
	return 0;
}
