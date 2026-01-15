#include <iostream>

/*
 * Curiously Recurring Template Pattern (CRTP)
 CRTP is used when you want to achieve static polymorphism.
 CRTP allows you to define a base class that can work with derived classes without knowing their exact types.
 The advantages of CRTP include:
 1. Improved performance: Since the polymorphism is resolved at compile-time, there is no runtime overhead.
 2. Code reuse: You can define common functionality in the base class and reuse it in derived classes.
 3. Better type safety: The compiler can catch errors related to type mismatches at compile-time.
 */

 // Basic way to implement CRTP
template <typename Derived>
class Base {
public:
    void interface() {
        // Call the derived class's implementation
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

/*
The above CRTP changes as below using deduced this in C++23
*/
template<typename Derived>
class Base1 {
public:
    void interface(this Derived& self) {
        // Call the derived class's implementation
        self.implementation();
    }
};

class Derived1 : public Base1<Derived1> {
public:
    void implementation() {
        std::cout << "Derived1 implementation" << std::endl;
    }
};


int main() {
    Derived d;
    d.interface();  // Calls the derived class's implementation

    Derived1 d1;
    d1.interface();  // Calls the derived class's implementation
    return 0;


}