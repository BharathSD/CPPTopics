#include <print>
#include <algorithm>
#include <ranges>
#include <vector>

namespace views = std::ranges::views;
/*
Cartesian product of two ranges can be done using views::cartesian_product.
Cartesian product is a mathematical operation that returns a set from multiple sets.
In the context of ranges, it produces a range of pairs (tuples) containing every combination
of elements from the input ranges.
This can be useful in various scenarios, such as generating test cases or exploring
combinations of parameters.
*/

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    // Compute the Cartesian product
    auto cartesian_product = views::cartesian_product(vec1, vec2);

    for (const auto& [x, y] : cartesian_product) {
        std::print("({}, {})\n", x, y);
    }

    return 0;
}