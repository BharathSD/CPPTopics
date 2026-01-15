#include <iostream>
#include <print>
#include <algorithm>
#include <functional>

int main() {
    std::function<int(int)> fact = [&](int n) -> int {
        if (n <= 1) return 1;
        return n * fact(n - 1);
    };

    std::println("Factorial of 5 is: {}", fact(5)); // Output: 120

    // another way to write the factorial function
    auto fact2 = [](auto self, int n) -> int {
        if (n <= 1) return 1;
        return n * self(self, n - 1);
    };

    std::println("Factorial of 5 is: {}", fact2(fact2, 5)); // Output: 120

    // the above one is a little clumsy that we have to call the function with itself
    // the next example shows how to avoid using this pointer using the lambda capture
    auto fact3 = [](this auto self, int n) -> int {
        if (n <= 1) return 1;
        return n * self(n - 1);
    };

    std::println("Factorial of 5 is: {}", fact3(5)); // Output: 120

    auto fact4 = [](this auto& self, int n) -> int {
        if (n <= 1) return 1;
        return n * self(n - 1);
    };

    std::println("Factorial of 5 is: {}", fact4(5)); // Output: 120


    // fibonacci using recursive lambdas
    auto fib = [](this auto& self, int n) -> int {
        if (n <= 1) return n;
        return self(n - 1) + self(n - 2);
    };

    std::println("Fibonacci of 5 is: {}", fib(5)); // Output: 5

    // sum of vector elements using recursive lambdas
    auto sum = [](this auto& self, const std::vector<int>& vec, int n) -> int {
        if (n <= 0) return 0;
        return self(vec, n - 1) + vec[n - 1];
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::println("Sum of vector elements is: {}", sum(vec, vec.size())); // Output: 15

    return 0;
}