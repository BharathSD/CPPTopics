#include <iostream>
#include <print>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ranges>

struct CPerson {
    std::string name;
    int age;
};

int main() {
    std::vector<int> vec1 = {5, 2, 8, 1, 4};
    std::print("Original vector: {}\n", vec1);

    // Sort the vector in ascending order
    std::ranges::sort(vec1);
    std::print("Sorted vector: {}\n", vec1);

    // Find the minimum element
    auto min_it = std::ranges::min_element(vec1);
    std::print("Minimum element: {}\n", *min_it);

    // Find the maximum element
    auto max_it = std::ranges::max_element(vec1);
    std::print("Maximum element: {}\n", *max_it);

    // sorting with projections
    std::ranges::sort(vec1, std::greater{});
    std::print("Sorted vector (descending): {}\n", vec1);


    std::vector<CPerson> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    // Sort people by age
    std::ranges::sort(people, {}, &CPerson::age);
    std::print("People sorted by age: {}\n", people);

    // old way of doing this is with std::sort
    std::sort(people.begin(), people.end(), [](const CPerson& a, const CPerson& b) {
        return a.age > b.age;
    });
    std::print("People sorted by age (old way): {}\n", people);

    // sort by name and age
    std::ranges::sort(people, [](const CPerson& a, const CPerson& b) {
        if (a.name == b.name)
            return a.age < b.age;
        return a.name < b.name;
    });
    std::print("People sorted by name and age: {}\n", people);


    // sort filter view
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7};
    auto even_numbers = numbers | std::views::filter([](int n) { return n % 2 == 0; })
                        | std::views::transform([](int n) { return n * 2; })
                        | std::ranges::to<std::vector>();
    std::ranges::sort(even_numbers);
    std::print("Sorted even numbers: {}\n", even_numbers);

    return 0;
}