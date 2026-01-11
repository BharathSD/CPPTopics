#include <iostream>
#include <concepts>
#include <vector>
#include <string>
#include <algorithm>

template<typename T>
concept HasSize = requires(T a) {
    { a.size() } -> std::same_as<std::size_t>;
};

auto getSize(const HasSize auto& container) {
    return container.size();
}

template <typename T>
concept defaultConstructable = requires() {
    T{};
};

// multiple template paramter examples
template <typename T, typename U>
concept Addable = requires(T a, U b) {
    { a + b } -> std::same_as<decltype(a + b)>;
};

// equality comparable
template <typename T, typename U>
concept EqualityComparable = requires(T a, U b) {
    { a == b } -> std::same_as<bool>;
};

// Sortable concept
template <typename T>
concept Sortable = requires(T a) {
    { std::sort(a.begin(), a.end()) };
};

// another way to define Sortable concept
/*
std::declval<T>() is a way to create a temporary object of type T without actually constructing it.
*/
template <typename T>
concept Sortable_1 = requires {
    std::sort(std::declval<T>().begin(), std::declval<T>().end()) ;
};

// streamable concept
template <typename T>
concept Streamable = requires{
    std::cout << std::declval<T>() ;
};

template <typename T>
concept ConstReference = std::is_reference_v<T> && std::is_const_v<std::remove_reference_t<T>>;

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Size of vector: " << getSize(vec) << std::endl;

    std::string str = "Hello";
    std::cout << "Size of string: " << getSize(str) << std::endl;

    return 0;
}