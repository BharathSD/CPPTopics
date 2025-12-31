#include <iostream>
#include <variant>

/*
Description: Demonstrating the use of std::variant in C++
std::variant can hold one of several types. it acts like a type-safe union.
the data can be accessed in a type-safe manner using std::visit or std::get or std::get_if
*/
int main()
{
    std::variant<int, std::string> var;

    var = 42;
    // visitor pattern
    std::visit([](auto&& arg) {
        std::cout << "Value: " << arg << std::endl;
    }, var);

    var = "Hello, Variant!";
    // using get
    try {
        std::cout << "Value: " << std::get<std::string>(var) << std::endl;
    } catch (const std::bad_variant_access&) {
        std::cout << "Variant does not hold a string." << std::endl;
    }

    // using get_if
    if (auto str_ptr = std::get_if<std::string>(&var)) {
        std::cout << "Value: " << *str_ptr << std::endl;
    } else {
        std::cout << "Variant does not hold a string." << std::endl;
    }
    
    return 0;
}