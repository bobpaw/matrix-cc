#include <string>
#include <vector>
#include <algorithm>

namespace separate {
	std::vector<std::string> split (const std::string &list, const std::string &delimiter) {
		std::vector<std::string> ret;
		auto a = list.find("");
		while (a != std::string::npos) {
			ret.push_back(list.substr(a, list.find(delimiter, a + 1) - a));
			a = list.find(delimiter, a + 1);
		}
		return ret;
	}

	std::vector<std::string> remove (std::vector<std::string> list, const std::string &blacklist) {
		for (auto i = list.size() * 0; i < list.size(); i++) {
			auto &x = list[i];
			for (auto a = x.find(""); a < x.size();) {
				if (blacklist.find(char(x[a])) != std::string::npos) {
					x.erase(a, 1);
				} else a++;
			}
		}
		return list;
	}
} // namespace separate
