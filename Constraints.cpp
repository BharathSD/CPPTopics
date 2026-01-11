#include <iostream>
#include <concepts>

/*
Constraints are logical conditions that a template argument must satisfy.
*/
template<typename T>
requires std::is_arithmetic_v<T>
auto add(const T& a, const T& b)  {
    return a + b;
}

// another way to write the same concept
template<typename T>
auto add_1(const T& a, const T& b)  requires std::is_arithmetic_v<T> {
    return a + b;
}

// another way to define the concept
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
requires Arithmetic<T>
auto add_2(const T& a, const T& b)  {
    return a + b;
}

// yet another way to define concept
template<Arithmetic T>
auto add_3(const T& a, const T& b) {
    return a + b;
}

// yet another way to define concept
auto add_4(const Arithmetic auto& a, const Arithmetic auto& b) {
    return a + b;
}

int main(){
    std::cout << add(3, 4) << std::endl;       // Works
    std::cout << add(3.5, 4.5) << std::endl;   // Works
    // std::cout << add("Hello", "World") << std::endl; // Error

    std::cout << add_1(3, 4) << std::endl;       // Works
    std::cout << add_1(3.5, 4.5) << std::endl;   // Works
    // std::cout << add_1("Hello", "World") << std::endl; // Error

    std::cout << add_2(3, 4) << std::endl;       // Works
    std::cout << add_2(3.5, 4.5) << std::endl;   // Works
    // std::cout << add_2("Hello", "World") << std::endl; // Error

    std::cout << add_3(3, 4) << std::endl;       // Works
    std::cout << add_3(3.5, 4.5) << std::endl;   // Works
    // std::cout << add_3("Hello", "World") << std::endl; // Error

    std::cout << add_4(3, 4) << std::endl;       // Works
    std::cout << add_4(3.5, 4.5) << std::endl;   // Works
    // std::cout << add_4("Hello", "World") << std::endl; // Error

    return 0;
}