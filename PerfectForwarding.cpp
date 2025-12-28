/*
std::forward is a utility in C++ used for perfect forwarding in template functions.
Perfect forwarding means passing arguments to another function while preserving their value category (lvalue or rvalue).
This is important in generic code, such as function templates, to avoid unnecessary copies and to ensure that move semantics are used when possible.

std::forward<T>(arg) will forward 'arg' as an rvalue if T is an rvalue reference, and as an lvalue if T is an lvalue reference.
This enables writing wrapper functions that can pass their arguments to other functions exactly as received, supporting both lvalues and rvalues efficiently.

Example:
template <typename T>
void wrapper(T&& arg) {
    callee(std::forward<T>(arg)); // preserves lvalue/rvalue nature
}
*/
#include <iostream>

// create some helper functions
void somefunction(int x, int y) {
    std::cout << "In Interger argument function" << std::endl;
}

void someFunction(float a, float b) {
    std::cout << "In Float argument function" << std::endl;
}

void singleArgFunc(int x) {
    std::cout << "In Single Integer argument function" << std::endl;
}

void singleArgFunc(float x) {
    std::cout << "In Single Float argument function" << std::endl;
}

template <typename... Args>
void functionWrapper(Args&&... args) {
    // Forward the arguments to somefunction
    somefunction(std::forward<Args>(args)...);
}

template <typename T>
void singleArgFuncWrapper(T&& arg) {
    singleArgFunc(std::forward<T>(arg));
}

int main() {
    int a = 5, b = 10;
    functionWrapper(a, b);

    float c = 1.0f, d = 2.0f;
    functionWrapper(c, d);

    singleArgFuncWrapper(a);
    singleArgFuncWrapper(c);

    return 0;
}
