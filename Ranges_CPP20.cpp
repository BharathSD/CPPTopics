#include <iostream>
#include <vector>
#include <map>
#include <ranges>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};


    // Using ranges
    std::cout << "Using Ranges views:\n";
    std::cout << "filter views:\n";
    for (const auto& element : vec | std::views::filter([](int n) { return n % 2 == 0; })) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using transform
    std::cout << "transform views:\n";
    for (const auto& element : vec | std::views::transform([](int n) { return n * 2; })) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using take
    std::cout << "take views:\n";
    for (const auto& element : vec | std::views::take(3)) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using take_while
    std::cout << "take_while views:\n";
    auto condition = [](int n) { return n < 4; };
    for (const auto& element : vec | std::views::take_while(condition)) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using reverse
    std::cout << "reverse views:\n";
    for (const auto& element : vec | std::views::reverse) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using drop
    std::cout << "drop views:\n";
    for (const auto& element : vec | std::views::drop(2)) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using as_const
    std::cout << "as_const views:\n";
    for (const auto& element : vec | std::views::as_const) {
        std::cout << element << " ";
        // element = 10; // Error: cannot modify const element
    }
    std::cout << std::endl;

    // using to_array
    std::cout << "to_array views:\n";
    auto arr = vec | std::views::chunk(2);
    for (const auto& subrange : arr) {
        for (const auto& element : subrange) {
            std::cout << element << " ";
        }
        std::cout << "| ";
    }

    // using is_even
    std::cout << "\nis_even lambda  with filter views:\n";
    auto is_even = [](int n) { return n % 2 == 0; };
    for (const auto& element : vec | std::views::filter(is_even)) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using is_prime
    std::cout << "\nis_prime lambda  with filter views:\n";
    auto is_prime = [](int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    };
    for (const auto& element : vec | std::views::filter(is_prime)) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using keys, works only for associative containers like std::map and std::unordered_map
    // create a map
    std::map<int, int> my_map {{1, 2}, {3, 4}, {5, 6}};
    std::cout << "\nkeys view of map:\n";
    for (const auto& element : my_map | std::views::keys) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using values, works only for associative containers like std::map and std::unordered_map
    std::cout << "\nvalues view of map:\n";
    for (const auto& element : my_map | std::views::values) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // using elements
    std::cout << "\nelements view of map:\n";
    for (const auto& element : my_map | std::views::elements<1>) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    // since elements<1> is mentioned, it gives the values. If elements<0> were mentioned, it would give the keys.

    // combining multiple views
    std::cout << "combining multiple views:\n";
    auto multiply_by2 = [](int n) { return n * 2; };
    for (const auto& element : vec | std::views::filter(is_even) | std::views::transform(multiply_by2)) {
        std::cout << element << " ";
    }
    std::cout << std::endl;


    // Range factories
    std::cout << "Range factories iota :\n";
    auto seq = std::views::iota(1, 10) | std::views::transform([](int n) { return n * n; });
    for (const auto& element : seq) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // single views
    std::cout << "Range factories : single views :\n";
    auto one = std::views::single(2);
    for (const auto& element : one) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // much cleaner use case of concatenating ranges (concat is not in C++20, so use join with a range of ranges)
    // Use std::vector of std::vector<int> to store the values
    std::cout << "combined ranges:\n";
    auto range = std::views::iota(1, 5);
    std::vector<std::vector<int>> combined_ranges_vec = {
        {2},
        std::vector<int>(range.begin(), range.end())
    };
    auto combined = combined_ranges_vec | std::views::join;
    for (const auto& element : combined) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // repeated use case
    std::cout << "repeated use case:\n";
    auto repeated = std::views::repeat(7, 5);
    for (const auto& element : repeated) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}