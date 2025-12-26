#include <iostream>

// Important note:
// lvalue: an expression that refers to a memory location
// rvalue: an expression that does not refer to a memory location

// function overloading with rvalue reference
void foo(int& x) { std::cout << "lvalue\n"; }
void foo(int&& x) { std::cout << "rvalue\n"; }

int main() {
    int a = 10;
    foo(a);          // lvalue
    foo(20);        // rvalue
    foo(a + 30);  // rvalue
    foo(std::move(a)); // rvalue, move semantics


    // important move semantics trait
    // std::move is used to cast an lvalue to an rvalue
    // enabling the use of move semantics
    int&& y = std::move(a);

    std::string s1 = "hello";
    std::string s2 = std::move(s1); // move semantics
    std::cout << "String contents after move: " << s1 << std::endl;
    std::cout << "String contents after move: " << s2 << std::endl;

    return 0;
}