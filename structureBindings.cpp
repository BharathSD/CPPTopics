#include <iostream>
#include <map>

std::pair<int, std::string> get_data() {
    return {42, "hello"};
}

int main() {
    std::pair<int, double> myPair = {1, 2.5};
    auto [myInt, myDouble] = myPair;

    std::cout << "Integer: " << myInt << ", Double: " << myDouble << std::endl;

    std::map<std::string, int> mymap = {{"a", 1}, {"b", 2}};

    for (const auto& [key, value] : mymap) {
        std::cout << key << ": " << value << '\n';
    }

    auto [myInt2, myString] = get_data();
    std::cout << "Integer: " << myInt2 << ", String: " << myString << std::endl;

    return 0;
}