#include <print>
#include <ranges>
#include <vector>
#include <numeric>

namespace views = std::ranges::views;

int main() {
    std::vector<std::pair<int, char>> vec = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'}
    };

    // Separate keys and values using views
    auto keys = vec | views::keys;
    auto values = vec | views::values;

    std::print("Keys: ");
    for (const auto& key : keys) {
        std::print("{} ", key);
    }

    std::print("\nValues: ");
    for (const auto& value : values) {
        std::print("{} ", value);
    }

    return 0;
}