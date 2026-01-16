#include <ranges>
#include <print>
#include <vector>
#include <numeric>

/*
std::views::chunk is a view adaptor that splits a range into chunks of a specified size.
This is useful when you want to process elements in groups.
This does not create an intermediate container. So no additional memory is allocated for the chunked view.
*/
int main() {
    std::vector<int> vec(12);
    std::iota(vec.begin(), vec.end(), 1);

    // below code chunks the vector into groups of 2
    // this is useful when you want to process elements in batches
    auto chunked = vec | std::views::chunk(2);
    for (const auto& chunk : chunked) {
        std::print("[");
        for (const auto& elem : chunk) {
            std::print("{:>2} ", elem);
        }
        std::print("]\n");
    }
    return 0;
}