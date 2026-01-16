#include <ranges>
#include <vector>
#include <numeric>
#include <print>
#include <algorithm>
/*
std::views::zip is a view adaptor that combines multiple ranges into a single range of tuples.
This is useful when you want to iterate over multiple containers in parallel.
This does not create an intermediate container. So no additional memory is allocated for the zipped view.
*/
int main() {
    std::vector<int> vec(12);
    std::iota(vec.begin(), vec.end(), 1);
    std::vector<std::string> str(12);
    std::transform(vec.begin(), vec.end(), str.begin(), [](int i) {
        return std::format("Value_{:0>2}", i);
    });
    for (auto [num, name] : std::views::zip(vec, str)) {
        std::println("{}: {:>2}", name, num);
    }

    // with non equal ranges
    std::println("Non-equal ranges:");
    auto reduced_vec = vec | std::views::take(8);
    for (auto [num, name] : std::views::zip(reduced_vec, str)) {
        std::println("{}: {:>2}", name, num);
    }

    // takes only the first 8 elements of both the vectors in the above case

    return 0;
}