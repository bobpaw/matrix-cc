#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <exception>

namespace matrix {
	struct MatrixMultException : std::exception {
		const char *what (void) const noexcept {
			return "Matrix multiplication error.";
		}
	};

	struct MatrixError : std::exception {
		const char *what (void) const noexcept {
			return "Column number was not uniform";
		}
	};

	struct MatrixAccessError : std::exception {
		const char *what (void) const noexcept {
			return "Matrix access starts at 1 and goes up to number of columns/rows";
		}
	};

	template<typename T = int>
	class Matrix {
		std::vector<std::vector<T>> data;
		std::size_t rows_, cols_;
	public:
		Matrix (int rows, int cols) : data(rows), rows_(rows), cols_(cols) {
			std::fill(data.begin(), data.end(), std::vector<T>(cols));
		}

		Matrix (std::vector<std::vector<T>> thing) : data(thing) {
			rows_ = data.size();
			cols_ = data[0].size();
			for (auto it = data.begin(); it != data.end(); ++it) if (it->size() != cols_) throw MatrixError();
		}

		int &at (int x, int y) {
			return data[y][x];
		}

		int & operator() (int x, int y) {
			if (y < 1 || y > rows_ || x < 1 || y > cols_) throw MatrixAccessError();
			return data[y - 1][x - 1];
		}

		explicit operator std::string() const {
			std::string ret = "[";
			std::string t;
			for (auto row : data) {
				ret += "[";
				for (auto item : row) {
					ret += std::to_string(item);
					ret += ",";
				}
				ret.pop_back();
				ret += "],";
			}
			ret.pop_back();
			ret += "]";
			return ret;
		}
		template <class type> friend std::ostream &operator<< (std::ostream &stream, const Matrix<type> &matrix);
	};

	auto I (int x) {
		Matrix<> a (x, x);
		for (int i = 0; i < x; i++) {
			a.at(i, i) = 1;
		}
		return a;
	}

	auto O (int x) {
		return Matrix<> (x,x);
	}

	template <class type> std::ostream &operator<< (std::ostream &stream, const Matrix<type> &matrix) {
		std::string t;
		stream << "[";
		for (auto row = matrix.data.begin(); row != matrix.data.end(); ++row) {
			stream << (row == matrix.data.begin() ? "[" : " [");
			for (auto item = row->begin(); item != row->end(); ++item) {
				t = std::to_string(*item);
				if (std::is_arithmetic<type>::value) for (auto i = t.size() ^ t.size(); i < 4 - t.size(); ++i) stream << " ";
				stream << t;
				if (std::next(item) != row->end()) stream << ",";
			}
			if (std::next(row) != matrix.data.end()) stream << "]," << std::endl;
		}
		stream << "]]";
		return stream;
	}

} // namespace
