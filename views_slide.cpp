#include <ranges>
#include <print>
#include <vector>
#include <numeric>
#include <algorithm>

/*

std::views::slide is a view adaptor that creates a sliding window over a range.
This is useful when you want to process elements in overlapping groups.
This does not create an intermediate container. So no additional memory is allocated for the sliding view.
*/

int main() {
    std::vector<int> vec(12);
    std::iota(vec.begin(), vec.end(), 1);
    auto slid = vec | std::views::slide(3);
    for (const auto& group : slid) {
        std::print("[");
        for (const auto& elem : group) {
            std::print("{:>2} ", elem);
        }
        std::print("]\n");
    }

    // print sum of each group
    for (const auto& group : slid) {
        auto sum = std::accumulate(group.begin(), group.end(), 0);
        std::print("Sum: {}\n", sum);
    }

    // print sum of 4 elements using sliding window using transform and save into a new vector
    // Compute sums of sliding windows of size 4 and store in a vector
    auto slid4 = vec | std::views::slide(4) | std::views::transform([](const auto& group) {
        return std::accumulate(group.begin(), group.end(), 0);
    });
    std::print("Sums : {}\n", slid4);

    // example of sliding window with step
    auto slid_step = vec | std::views::slide(4) | std::views::stride(2);
    for (const auto& group : slid_step) {
        std::print("[");
        for (const auto& elem : group) {
            std::print("{:>2} ", elem);
        }
        std::print("]\n");
    }

    // two dimensional sliding window

    std::println("\n2D Sliding window example:");
    std::vector<std::vector<int>> matrix(5, std::vector<int>(5));

    // fill matrix with random number between 0 and 99
    for (auto& row : matrix) {
        std::generate(row.begin(), row.end(), []() {
            return rand() % 100;
        });
    }
    std::println("\nOriginal Matrix:");
    // Print original matrix
    for (const auto& row : matrix) {
        std::print("[");
        for (const auto& elem : row) {
            std::print("{:>2} ", elem);
        }
        std::print("]\n");
    }

    std::println("\nSliding window of 2 rows:");
    auto slid2d = matrix | std::views::slide(2); // takes two rows at a time
    for (const auto& group : slid2d) {
        std::print("[");
        for (const auto& row : group) {
            std::print("[");
            for (const auto& elem : row) {
                std::print("{:>2} ", elem);
            }
            std::print("] ");
        }
        std::print("]\n");
    }

    return 0;
}