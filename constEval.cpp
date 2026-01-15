#include <iostream>

/*
consteval example
*/

constexpr int factorial(int n) {
    if (n <= 1) 
        return 1;
    else 
        return n * factorial(n - 1);
}

constexpr int compute(int x) {
    if consteval {
        // At compile time, calculate factorial and add a constant
        return factorial(x) + 100;
    } else {
        // At runtime, do a different calculation
        return x * x - 10;
    }
}

int main() {
    constexpr int result1 = compute(5);  // Should be evaluated at compile time
    int result2 = compute(10);             // Should be evaluated at runtime

    std::cout << "Compile-time result: " << result1 << std::endl;
    std::cout << "Run-time result: " << result2 << std::endl;

    return 0;
}