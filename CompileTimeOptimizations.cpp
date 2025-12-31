#include <iostream>

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

// another example fibonacci
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));
}


int main() {
    constexpr int result = factorial(5); // this is computed at compile time
    std::cout << "Factorial of 5 is: " << result << std::endl;

    constexpr int fib_result = fibonacci(15); // this is also computed at compile time
    std::cout << "Fibonacci of 15 is: " << fib_result << std::endl;

    return 0;
}