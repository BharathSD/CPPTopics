#include <print>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <print>

namespace views = std::ranges::views;

void padding(std::vector<std::vector<int>>& matrix, unsigned int pad_row, unsigned int pad_col) {
    // Apply padding using views on top and bottom each of size one row
    // views::concat cannot be used as it available only in c++26
    // Pad rows on top and bottom
    std::vector<int> row_data(matrix[0].size(), 0);
    for (unsigned int i = 0; i < pad_row; ++i) {
        matrix.insert(matrix.begin(), row_data);
        matrix.push_back(row_data);
    }
    // Pad columns on left and right for each row
    for (auto& row : matrix) {
        for (unsigned int j = 0; j < pad_col; ++j) {
            row.insert(row.begin(), 0);
            row.push_back(0);
        }
    }
}

std::vector<std::vector<int>> convolution(const std::vector<std::vector<int>>& input, 
                                            const std::vector<std::vector<int>>& kernel, 
                                            std::tuple<unsigned int, unsigned int> stride = {1, 1},
                                            std::tuple<unsigned int, unsigned int> padding_size = {0, 0}) {

    unsigned int win_rows = kernel.size();
    unsigned int win_cols = kernel[0].size();
    unsigned int mat_rows = static_cast<unsigned int>(input.size());
    unsigned int mat_cols = mat_rows > 0 ? static_cast<unsigned int>(input[0].size()) : 0;

    unsigned int stride_row = std::get<0>(stride);
    unsigned int stride_col = std::get<1>(stride);
    unsigned int pad_row = std::get<0>(padding_size);
    unsigned int pad_col = std::get<1>(padding_size);

    /*
    Check if convolution is possible by checking the valid output size based on input data size,
    kernel size, stride, and padding. Ideally, the output size should be positive and a whole number for both
    dimensions. If not, raise an exception.
    */

    unsigned int output_row_size_numerator = mat_rows - win_rows + pad_row * 2;
    unsigned int output_col_size_numerator = mat_cols - win_cols + pad_col * 2;
    if ((output_row_size_numerator % stride_row) != 0) {
        throw std::invalid_argument("Output row size is not a whole number (fractional output size).");
    }
    else if ((output_col_size_numerator % stride_col) != 0)
    {
        throw std::invalid_argument("Output column size is not a whole number (fractional output size).");
    }
    
    unsigned int output_row_size = (output_row_size_numerator / stride_row) + 1;
    unsigned int output_col_size = (output_col_size_numerator / stride_col) + 1;

    if (output_row_size == 0 || output_col_size == 0) {
        throw std::invalid_argument("Invalid output size");
    }


    auto padded_input = input;
    if(pad_row > 0 || pad_col > 0) {
        // Apply padding to the input matrix
        padding(padded_input, pad_row, pad_col);
    }

    auto all_windows = views::iota(0U, output_row_size)  // Row positions
        | views::stride(stride_row)
        | views::transform([&](unsigned int i) {
            return views::iota(0U, output_col_size)  // Column positions
                | views::stride(stride_col)
                | views::transform([&, i](unsigned int j) {
                    return padded_input 
                        | views::drop(i)    // Skip first i rows
                        | views::take(win_rows)    // Grab win_rows rows
                        | views::transform([&, j](const auto& row) {
                            return row | views::drop(j)  // Skip first j columns
                                       | views::take(win_cols); // Grab win_cols columns
                          });
                });
          })
        | views::join; // Flatten the outer view

    // Now lets do convolution operation
    // Create a convolution output of size (mat_rows - win_rows + 1) x (mat_cols - win_cols + 1)

    std::vector<std::vector<int>> result = 
                std::vector<std::vector<int>>(output_row_size, std::vector<int>(output_col_size));

    int window_index = 0;
    for (const auto& window : all_windows) {
        // Apply the kernel to the current window
        int sum = 0;
        for (unsigned int i = 0; i < win_rows; ++i) {
            for (unsigned int j = 0; j < win_cols; ++j) {
                sum += window[i][j] * kernel[i][j];
            }
        }
        result[window_index / output_col_size][window_index % output_col_size] = sum / (win_rows * win_cols);
        window_index++;
    }

    return result;
}

std::vector<std::vector<int>> create_sample_matrix(int rows, int cols) {
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols));
    for (auto& row : result) {
        std::generate(row.begin(), row.end(), []() {
            return rand() % 100;
        });
    }
    return result;
}

template<>
struct std::formatter<std::vector<std::vector<int>>> : std::formatter<std::string> {
    auto format(const std::vector<std::vector<int>>& mat, std::format_context& ctx) const {
        std::string result = "[\n";
        for (const auto& row : mat) {
            result += "  [ ";
            for (const auto& val : row) {
                result += std::format("{:>5} ", val);
            }
            result += "]\n";
        }
        result += "]";
        return std::formatter<std::string>::format(result, ctx);
    }
};

int main() {
    auto input = create_sample_matrix(15, 15);
    auto kernel = create_sample_matrix(3, 3);
    std::println("Input Matrix:\n{}", input);
    std::println("Kernel Matrix:\n{}", kernel);

    auto result = convolution(input, kernel);
    std::println("Convolution Result:\n{}", result);

    return 0;
}
