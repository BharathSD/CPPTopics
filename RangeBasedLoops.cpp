#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <map>
#include <unordered_map>
#include <set>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // traditional way
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // another way with iterators
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // Range-based for loop
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // list
    std::list<double> lst = {6.5, 7.8, 8.1, 9.8, 10.4};
    for (const auto& element : lst) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // deque
    std::deque<char> deq = {'A', 'B', 'C', 'D', 'E'};
    for (const auto& element : deq) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // array
    std::array<float, 5> arr = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // map
    std::map<std::string, int> myMap = {{"one", 1}, {"two", 2}, {"three", 3}};
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << " ";
    }
    std::cout << std::endl;

    // unordered_map
    std::unordered_map<std::string, int> myUnorderedMap = {{"apple", 1}, {"banana", 2}, {"cherry", 3}};
    for (const auto& [key, value] : myUnorderedMap) {
        std::cout << key << ": " << value << " ";
    }
    std::cout << std::endl;

    // set
    std::set<std::string> mySet = {"apple", "banana", "cherry"};
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // iterating over c style arrays
    int cStyleArray[] = {1, 2, 3, 4, 5};
    for (const auto& element : cStyleArray) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}