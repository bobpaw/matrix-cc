#include <iostream>
#include <string>
#include "container.h"

int main (int argc, char *argv[]) {
	std::string line;
	try {
	while (true) {
	  std::cout << "> " << std::flush;
	  std::getline(std::cin, line);
	  if (line.size() == 0 || std::string("exit").find(line) == 0 || std::string("quit").find(line) == 0) break;
	  container::TextHolder a(line, argc > 1 ? "[]" : "()");
	  std::cout << a.toFunString() << std::flush;
	  }
	} catch (const char *e) {
	  std::cerr << e << std::endl;
	  return -1;
	}
	if (std::cin.eof()) std::cout << std::endl << std::flush;
	return 0;
}
