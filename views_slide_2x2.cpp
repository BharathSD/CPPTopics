#include <print>
#include <vector>
#include <ranges>

namespace views = std::ranges::views;

int main() {
    // Example 2D matrix - imagine this is a grid of numbers, like a checkerboard
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3, 4},      // Row 0
        {5, 6, 7, 8},      // Row 1
        {9, 10, 11, 12},   // Row 2
        {13, 14, 15, 16}   // Row 3
    };
    
    int rows = matrix.size();     // How many rows? 4 rows
    int cols = matrix[0].size();  // How many columns? 4 columns
    auto win_rows {2};
    auto win_cols {2};

    // STEP 1: Make a list of all possible starting row positions (0, 1, 2)
    // We stop at rows-1 because we need 2 rows for our window!
    // Think: "Where can I place the TOP of my 2x2 window?"

    auto all_windows = views::iota(0, rows - win_rows + 1)  // Give me numbers: 0, 1, 2

        // STEP 2: For EACH row position, make a list of column positions
        | views::transform([&](int i) {
            // i is like saying "start at THIS row"
            
            return views::iota(0, cols - win_cols + 1)  // Give me numbers: 0, 1, 2
                // Think: "Where can I place the LEFT side of my 2x2 window?"
                
                // STEP 3: For EACH column position, create the actual window!
                | views::transform([&, i](int j) {
                    // Now i = row, j = column. Time to cut out our 2x2 piece!
                    
                    return matrix 
                        | views::drop(i)    // Skip first i rows (jump down)
                        | views::take(win_rows)    // Grab 2 rows
                        | views::transform([&, j](const auto& row) {
                            // For each of those 2 rows, cut out 2 columns
                            return row | views::drop(j)  // Skip first j columns (jump right)
                                       | views::take(win_cols); // Grab 2 columns
                        });
                    // Now we have a 2x2 window!
                });
        })
        | views::join;  // Flatten everything into one big list of windows
    
    // STEP 4: Look at each window one by one
    int window_num = 0;
    for (auto window : all_windows) {
        // Figure out which position this window is at
        int i = window_num / (cols - 1);
        int j = window_num % (cols - 1);
        
        std::print("Window at position ({}, {}):\n", i, j);
        
        // Print what's inside this 2x2 window
        for (const auto& row : window) {
            for (int val : row) {
                std::print("{} ", val);
            }
            std::print("\n");
        }
        std::print("\n");
        
        window_num++;
    }
    
    return 0;
}