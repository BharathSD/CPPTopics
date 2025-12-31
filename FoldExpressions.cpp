#include <iostream>
#include <vector>
#include <string>

int main() {
    /*
    This lambda prints all arguments passed to it.
    This is a c++17 feature called fold expressions.
    This expression expands the parameter pack and prints each argument.
    This is a comma operator in action.
    */
    auto print_all = [](const auto&... args) {
        ((std::cout << args << " "), ...);
        std::cout << "\n";
    };

    print_all(1, 2.5, "Hello");

    // unary right fold sum
    auto sum = [](const auto&... args) {
        return (args + ...);
    };

    std::cout << "Unary Right Fold Sum: " << sum(1, 2, 3, 4, 5) << "\n";

    // unary right fold product
    auto product = [](const auto&... args) {
        return (args * ...);
    };
    std::cout << "Unary Right Fold Product: " << product(1, 2, 3, 4, 5) << "\n";

    // unary left fold sum
    auto left_sum = [](const auto&... args) {
        return ( ... + args);
    };

    std::cout << "Unary Left Fold Sum: " << left_sum(1, 2, 3, 4, 5) << "\n";

    // unary left fold product
    auto left_product = [](const auto&... args) {
        return ( ... * args);
    };
    std::cout << "Unary Left Fold Product: " << left_product(1, 2, 3, 4, 5) << "\n";

    // sum with initial value
    auto sum_with_initial = [](const auto& initial, const auto&... args) {
        return (args + ...) + initial;
    };

    std::cout << "Unary Left Fold Sum with Initial: " << sum_with_initial(10, 1, 2, 3, 4, 5) << "\n";

    // sum with initial value (left fold)
    auto sum_with_initial_left = [](const auto& initial, const auto&... args) {
        return initial + (args + ...);
    };

    std::cout << "Unary Left Fold Sum with Initial (Left Fold): " << sum_with_initial_left(10, 1, 2, 3, 4, 5) << "\n";

    // logical And
    auto logical_and = [](const auto&... args) {
        return (args && ...);
    };

    std::cout << "Logical And: " << logical_and(true, false, true) << "\n";
    std::cout << "Logical And: " << logical_and(true, true, true) << "\n";

    // logical Or
    auto logical_or = [](const auto&... args) {
        return (args || ...);
    };

    std::cout << "Logical Or: " << logical_or(false, false, true) << "\n";
    std::cout << "Logical Or: " << logical_or(false, true, false) << "\n";

    // minimum using function (comma operator to enforce order) using fold expressions
    auto minAll = [](const auto& arg1, const auto&... args) {
        return (std::min)({arg1, args...});
    };

    std::cout << "Minimum: " << minAll(5, 2, 8, 1, 4) << "\n";

    // maximum using function (comma operator to enforce order) using fold expressions
    auto maxAll = [](const auto& arg1, const auto&... args) {
        return (std::max)({arg1, args...});
    };

    std::cout << "Maximum: " << maxAll(5, 2, 8, 1, 4) << "\n";

    // average using function (comma operator to enforce order) using fold expressions
    auto avgAll = [](const auto&... args) {
        return (static_cast<double>((args + ...)) / sizeof...(args));
    };

    std::cout << "Average: " << avgAll(5, 2, 8, 1, 4) << "\n";

    // concatenation of strings using fold expressions
    auto concatAll = [](const auto&... args) {
        return (std::string(args) + ...);
    };

    std::cout << "Concatenation: " << concatAll("Hello, ", "world", "!") << "\n";

    // container append
    std::vector<std::string> vec;
    auto appendToContainer = [&vec](const auto&... args) {
        (vec.push_back(args), ...);
    };

    appendToContainer("Hello", "world", "!");
    std::cout << "Container contents: ";
    for (const auto& str : vec) {
        std::cout << str << " ";
    }
    std::cout << "\n";

    // bitwise And
    auto bitwise_and = [](const auto&... args) {
        return (args & ...);
    };

    std::cout << "Bitwise And: " << bitwise_and(5, 3, 1) << "\n";

    // bitwise Or
    auto bitwise_or = [](const auto&... args) {
        return (args | ...);
    };

    std::cout << "Bitwise Or: " << bitwise_or(5, 3, 1) << "\n";

    // bitwise Xor
    auto bitwise_xor = [](const auto&... args) {
        return (args ^ ...);
    };

    std::cout << "Bitwise Xor: " << bitwise_xor(5, 3, 1) << "\n";

    // bitwise Or
    auto bitwise_or = [](const auto&... args) {
        return (args | ...);
    };

    std::cout << "Bitwise Or: " << bitwise_or(5, 3, 1) << "\n";

    return 0;
}
