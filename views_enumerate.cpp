#include <print>
#include <ranges>
#include <vector>
#include <numeric>
#include <algorithm>

namespace views = std::ranges::views;

/*
enumerate a range can be done using views::enumerate, it is very useful for getting 
both the index and the value while iterating. this is particularly useful in algorithms
where you need to keep track of the position of elements.
*/
int main() {
    std::vector<int> vec(12);
    // lets set random numbers
    std::generate(vec.begin(), vec.end(), std::rand);

    // Use views to enumerate the vector
    for (const auto& [index, value] : views::enumerate(vec)) {
        std::print("Element at index {} is {}\n", index, value);
    }

    return 0;
}
