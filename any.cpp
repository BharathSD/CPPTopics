#include <iostream>
#include <any>
#include <vector>

/*
std::any can hold any type of value.
using std::any_cast, we can retrieve the value stored in std::any.
if the cast is wrong, std::bad_any_cast exception is thrown.
advantage of std::any is its ability to hold any type without knowing the type in advance.
Disadvantage of std::any is that it incurs some runtime overhead due to type erasure.
*/
int main() {
    std::any a = 42;
    std::cout << "Value: " << std::any_cast<int>(a) << std::endl;

    a = std::string("Hello, Any!");
    std::cout << "Value: " << std::any_cast<std::string>(a) << std::endl;

    try
    {
        std::cout << "Value: " << std::any_cast<double>(a) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Type: " << a.type().name() << std::endl;

    std::cout << "has value: " << a.has_value() << std::endl;
    a.reset();
    std::cout << "has value: " << a.has_value() << std::endl;

    std::vector<std::any> vec;
    vec.push_back(42);
    vec.push_back(std::string("Hello, Any!"));
    vec.push_back(3.14);


    return 0;
}