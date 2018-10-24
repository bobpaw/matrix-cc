#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <exception>

namespace matrix {
	struct MatrixMultError : std::exception {
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
			return "Matrix access error, out of bounds";
		}
	};

	template<typename T = int> class Matrix;
	template <typename> struct isMatrix : public std::false_type {};
	template <typename T> struct isMatrix<Matrix<T>> : public std::true_type {};

	template<typename T>
	class Matrix {
		std::vector<std::vector<T>> data;
		std::size_t rows_, cols_;
	public:

		decltype(rows_) rows (void) const { return rows_; }
		decltype(cols_) cols (void) const { return cols_; }

		Matrix (int rows, int cols) : data(rows), rows_(rows), cols_(cols) {
			std::fill(data.begin(), data.end(), std::vector<T>(cols));
		}

		Matrix (std::vector<std::vector<T>> thing) : data(thing) {
			rows_ = data.size();
			cols_ = data[0].size();
			for (auto it = data.begin(); it != data.end(); ++it) if (it->size() != cols_) throw MatrixError();
		}

		Matrix (const Matrix<T> &old) : data(old.data), rows_(old.rows_), cols_(old.cols_) {
		}

		T &at (int x, int y) {
			return data[y][x];
		}

		T at (int x, int y) const {
			return data[y][x];
		}

		T &operator() (decltype(cols_) x, decltype(rows_) y) {
			if (y < 1 || y > rows_ || x < 1 || x > cols_) throw MatrixAccessError();
			return data[y - 1][x - 1];
		}

		T operator() (decltype(cols_) x, decltype(rows_) y) const {
			if (y < 1 || y > rows_ || x < 1 || y > cols_) throw MatrixAccessError();
			return data[y - 1][x - 1];
		}

		Matrix<T> row (int y) const {
			--y;
			Matrix<T> ret(1, cols_);
			for (decltype(cols_) i = 0; i < cols_; i++) {
				ret.at(i, y) = at(i, y);
			}
			return ret;
		}

		Matrix<T> col (int x) const {
			--x;
			Matrix<T> ret(rows_, 1);
			for (decltype(rows_) i = 0; i < rows_; ++i) {
				ret.at(x, i) = at(x, i);
			}
			return ret;
		}

		Matrix<T> transpose (void) const {
			Matrix<T> ret(cols_, rows_);
			for (decltype(rows_) y = 0; y < rows_; ++y) {
				for (decltype(cols_) x = 0; x < cols_; ++x) {
					ret.at(x, y) = at(y, x);
				}
			}
			return ret;
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
		template <class type>
		typename std::enable_if<std::is_arithmetic<type>::value, Matrix<type>>::type operator* (const Matrix<type> &rhs) const {
			if (cols_ != rhs.rows_) throw MatrixMultError();
			Matrix<type> ors = rhs.transpose();
			Matrix<type> ret(rows_, rhs.cols_);
			for (decltype(ret.rows_) y = 0; y < ret.rows_; ++y) {
				for (decltype(ret.cols_) x = 0; x < ret.cols_; ++x) {
					for (decltype(cols_) i = 0; i < cols_; ++i) {
						ret.at(x, y) += data[y][i] * ors.data[x][i];
					}
				}
			}
			return ret;
		}

		template <typename type>
		Matrix<T> operator* (const type &rhs) const {
			Matrix<T> ret(rows_, cols_);
			for (decltype(rows_) y = 0; y < rows_; ++y) {
				for (decltype(cols_) x = 0; x < rows_; ++x) {
					ret.at(x, y) = at(x, y) * rhs;
				}
			}
			return ret;
		}

		template <typename type, typename matrix_type> friend typename std::enable_if<!isMatrix<type>::value, Matrix<matrix_type>>::type operator* (const type &lhs, const Matrix<matrix_type> &rhs);
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

	template <typename type, typename matrix_type>
	typename std::enable_if<!isMatrix<type>::value, Matrix<matrix_type>>::type operator* (const type &lhs, const Matrix<matrix_type> &rhs) {
		Matrix<matrix_type> ret(rhs.rows_, rhs.cols_);
		for (decltype(rhs.rows_) y = 0; y < rhs.rows_; ++y) {
			for (decltype(rhs.cols_) x = 0; x < rhs.rows_; ++x) {
				ret.at(x, y) = lhs * rhs.at(x, y);
			}
		}
		return ret;
	}
} // namespace
