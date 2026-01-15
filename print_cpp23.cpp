#include <iostream>
#include <print>
#include <vector>
#include <map>
#include <tuple>
#include <variant>
#include <string>
#include <any>

template<>
struct std::formatter<std::variant<int, double, std::string>> : std::formatter<std::string> {
    auto format(const std::variant<int, double, std::string>& var, std::format_context& ctx) const {
        return std::visit([&](const auto& val) {
            if constexpr (std::is_same_v<std::decay_t<decltype(val)>, std::string>)
                return std::formatter<std::string>::format(val, ctx);
            else
                return std::formatter<std::string>::format(std::to_string(val), ctx);
        }, var);
    }
};


using std::print;

int main() {
    print("Hello, World!\n");

    print("{}, {}\n", 42, 3.14);

    std::vector<int> numbers = {1, 2, 3, 4, 5};
    print("Numbers: {}\n", numbers);

    std::vector<std::string> fruits = {"apple", "banana", "cherry"};
    print("Fruits: {}\n", fruits);

    std::map<std::string, int> ageMap = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    print("Ages: {}\n", ageMap);

    std::variant<int, double, std::string> v = "hello";
    print("variant holds: {}\n",  v);

    std::tuple<int, std::string, double> person = {1, "Alice", 29.5};
    print("Person: {}\n", person);

    std::any a = 42;
    print("any holds: {}\n", std::any_cast<int>(a));

    return 0;
}