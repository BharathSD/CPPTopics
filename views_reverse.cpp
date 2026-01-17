#include <print>
#include <ranges>
#include <vector>
#include <numeric>

namespace views = std::ranges::views;


int main() {
    std::vector<int> vec(20);
    std::iota(vec.begin(), vec.end(), 1);  // Fill with values 1 to 20

    // Reverse the vector using views
    auto reversed = vec | views::reverse;

    for (const auto& elem : reversed) {
        std::print("{} ", elem);
    }
    return 0;
}