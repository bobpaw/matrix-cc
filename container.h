#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace container {
  class TextHolder {
  private:
		std::remove_const<decltype(std::string::npos)>::type begin, end; // Beginning in str_ init string
		bool bigness_; // Is is the largest
		std::string str_; // String initially passed
	protected:
		std::vector<TextHolder> children_; // Children vector
		std::string quotes_; // Two character string
		std::vector<std::string> items_; // List of all items
		std::string item_; // Concatenated items
		std::size_t num_; // Number of items
	public:
		decltype(items_) &items (void) { return items_; }
		std::string &item (std::string::size_type n) { return items_[n]; }
		decltype(item_) &item (void) { return item_; }
		decltype(bigness_) bigness (void) const { return bigness_; }
		decltype(num_) num (void) const { return num_; }

		TextHolder () : TextHolder("") {}
		TextHolder (const std::string &init, std::string quotestr = "()", std::string::size_type find = 0, bool big = true) : bigness_(big), quotes_(quotestr) {
			if (quotes_.size() != 2) throw "Wrong size quotestring";
			children_.reserve(init.size()/2);
			begin = find;
			if (init.size() != 0) {
				while (true) {
					find = init.find_first_of(quotestr, bigness_ && find == 0 ? find : find + 1);
					if (init[find] == quotestr[0]) {
						if (find != begin + 1) {
							int oldend;
							if (children_.size() > 0) {
								oldend = children_.back().end + 1;
							} else {
								oldend = begin + 1;
							}
							items_.push_back(init.substr(oldend, find - oldend));
						}
						children_.push_back(TextHolder(init, quotestr, find, false));
						find = children_.back().end;
					} else if (init[find] == quotestr[1]) {
						if (find != begin + 1) {
							int oldend;
							if (children_.size() > 0) {
								oldend = children_.back().end + 1;
							} else {
								oldend = begin + 1;
							}
							items_.push_back(init.substr(oldend, find - oldend));
						}
						end = find;
						if (!bigness_ || end == init.length() - 1) break;
					} else if (find == std::string::npos) {
						break;
					} else {
						throw "Error";
					}
				}
			}
			if (!big) {
				str_ = init.substr(begin, end - begin);
			} else {
				str_ = init;
			}
			for (auto i : items_) item_.append(i);
			if (!bigness_) {
				num_ = children_.size();
			} else {
				num_ = children_[0].children_.size();
			}
		}

		TextHolder &operator[] (std::vector<TextHolder>::size_type n) {
			if (!bigness_) {
				if (n > children_.size() - 1) throw std::out_of_range("TextHolder out of children bounds");
				return children_[n];
			} else {
				if (n > children_[0].children_.size() - 1) throw std::out_of_range("TextHolder out of children bounds");
				return children_[0].children_[n];
			}
		}

		std::string toFunString (std::string tab = "  ", int depth = 0) const {
			std::string ret = "";
			for (int i = 0; i < depth; ++i) ret.append(tab);
			if (!bigness_) ret += quotes_[0] + item_;
			if (children_.size() != 0) {
				if (!bigness_) ret += '\n';
				if (!bigness_) depth++;
				for (auto child : children_) ret.append(child.toFunString(tab, depth));
				if (!bigness_) depth--;
				for (int i = 0; i < depth; ++i) ret.append(tab);
			}
			if (!bigness_) ret += quotes_[1];
			if (!bigness_) ret += '\n';
			return ret;
		}
	};

}
