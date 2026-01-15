#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <format>
#include <print>

template<typename T>
requires std::is_arithmetic_v<T>
class Matrix {
    std::vector<std::vector<T>> data;

public:
    // Constructor
    Matrix(size_t rows = 1, size_t cols = 1) : data(rows, std::vector<T>(cols)) {}

    Matrix(const std::vector<std::vector<T>>& init) : data(init) {}

    Matrix(Matrix&& other) noexcept = default;

    Matrix& operator=(Matrix&& other) noexcept = default;

    void initializeRandomly() {
        for (auto& row : data) {
            std::generate(row.begin(), row.end(), []() {
                return static_cast<T>(rand() % 100);  // Random values between 0 and 99
            });
        }
    }

    // Sum of a specific column
    T sumCol(size_t col) const {
        T sum = T{};
        for (const auto& row : data) {
            if (col < row.size()) {
                sum += row[col];
            }
        }
        return sum;
    }

    // Sum of a specific row
    T sumRow(size_t row) const {
        return std::accumulate(data[row].begin(), data[row].end(), T{});
    }

    // 2D access operator
    const T& operator[](size_t row, size_t col) const {
        return data[row][col];
    }
    T& operator[](size_t row, size_t col) {
        return data[row][col];
    }

    size_t rows() const { return data.size(); }
    size_t cols() const { return data.empty() ? 0 : data[0].size(); }
};

template<typename T>
struct std::formatter<Matrix<T>> : std::formatter<std::string> {
    auto format(const Matrix<T>& mat, std::format_context& ctx) const {
        std::string result = "[\n";
        for (size_t i = 0; i < mat.rows(); ++i) {
            result += "  [ ";
            for (size_t j = 0; j < mat.cols(); ++j) {
                result += std::format("{}", mat[i, j]);
                if (j != mat.cols() - 1) {
                    result += ", ";
                }
            }
            result += " ]\n";
        }
        result += "]";
        return std::formatter<std::string>::format(result, ctx);
    }
};

int main() {
    // Create a 2D vector (matrix)
    Matrix<int> mat(3, 4);
    mat.initializeRandomly();

    // Print the matrix
    std::println("Matrix : \n{}", mat);

    return 0;
}