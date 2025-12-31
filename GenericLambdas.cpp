#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    auto print = [](const auto& container) {
        for (const auto& elem : container) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    };

    std::vector<int> intVec = {1, 2, 3, 4, 5};
    std::vector<double> doubleVec = {1.1, 2.2, 3.3};

    print(intVec);
    print(doubleVec);

    std::vector<std::string> stringVec = {"Hello", "World"};
    print(stringVec);

    auto genericLambda = [](const auto& a, const auto& b) {
        return a + b;
    };

    std::cout << "Generic Lambda (int): " << genericLambda(5, 10) << "\n";
    std::cout << "Generic Lambda (double): " << genericLambda(5.5, 10.5) << "\n";

    auto print_all = [](const auto&... args) {
        /*
        This lambda prints all arguments passed to it.
        This is a c++17 feature called fold expressions.
        This expression expands the parameter pack and prints each argument.
        */
        ((std::cout << args << " "), ...);
        std::cout << "\n";
    };

    print_all(1, 2.5, "Hello");

    return 0;
}