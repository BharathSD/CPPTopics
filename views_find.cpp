#include <print>
#include <ranges>
#include <vector>
#include <numeric>
#include <iostream>

namespace views = std::ranges::views;

int main() {
    std::vector<int> vec(20);
    std::iota(vec.begin(), vec.end(), 1);  // Fill with values 1 to 20

    // Find the first element greater than 10
    auto it = vec | views::filter([](int n) { return n > 10; });
    if (!it.empty()) {
        std::print("First element greater than 10: {}\n", *it.begin());
    }

    auto it1 = std::ranges::find(vec, 15);
    if (it1 != vec.end()) {
        std::cout << "Found element : " << *it1 << '\n';
    } else {
        std::cout << "Element 15 not found\n";
    }

    auto it3 = std::ranges::find(vec, 25);
    if (it3 != vec.end()) {
        std::cout << "Found element : " << *it3 << '\n';
    } else {
        std::cout << "Element 25 not found\n";
    }

    auto it4 = std::ranges::find_if(vec, [](int x) { return x > 10; });
    if (it4 != vec.end()) {
        std::cout << "Found element greater than 10: " << *it4 << '\n';
    } else {
        std::cout << "No element found greater than 10\n";
    }

    auto it5 = std::ranges::find_if(vec, [](int x) { return x < 5; });
    if (it5 != vec.end()) {
        std::cout << "Found element less than 5: " << *it5 << '\n';
    } else {
        std::cout << "No element found less than 5\n";
    }

    auto it6 = std::ranges::find_if(vec, [](int x) { return x == 10; });
    if (it6 != vec.end()) {
        std::cout << "Found element equal to 10: " << *it6 << '\n';
    } else {
        std::cout << "No element found equal to 10\n";
    }

    return 0;
}
