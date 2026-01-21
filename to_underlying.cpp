#include <iostream>
#include <bitset>
#include <format>
#include <type_traits>
#include <string_view>
#include <array>
#include <vector>
#include <utility>
#include <print>

enum class Color : uint8_t { Red = 1, Green = 2, Blue = 4 };
enum class Status : int { Ok = 0, Warning = 1, Error = 2 };
enum class Permission : unsigned { Read = 1, Write = 2, Execute = 4 };

int main() {
    // 1. Store enum as integer
    Color c = Color::Green;
    auto c_val = std::to_underlying(c);
    std::println("Color::Green as int: {}", static_cast<int>(c_val));

    // 2. Use as bitmask
    Permission p = Permission::Read;
    unsigned mask = std::to_underlying(p) | std::to_underlying(Permission::Write);
    std::println("Read|Write mask: {}", std::bitset<3>(mask));

    // 3. Switch on enum underlying value
    Status s = Status::Warning;
    switch (std::to_underlying(s)) {
        case 0: std::println("Status OK"); break;
        case 1: std::println("Status Warning"); break;
        case 2: std::println("Status Error"); break;
    }

    // 4. Use as array index
    std::array<std::string_view, 3> status_names = { "Ok", "Warning", "Error" };
    std::println("Status name: {}", status_names[std::to_underlying(s)]);

    // 5. Store enums in a vector of ints
    std::vector<Color> colors = { Color::Red, Color::Blue };
    for (Color col : colors) {
        std::println("Color value: {}", std::to_underlying(col));
    }

    // 6. Format enum as integer
    std::println("Color::Red as int: {}", std::to_underlying(Color::Red));

    // 7. Use in std::pair or std::map as key
    std::pair<Color, int> color_count{Color::Blue, 5};
    std::println("Pair: ({}, {})", std::to_underlying(color_count.first), color_count.second);

    // 8. Perform arithmetic operations
    unsigned perm_val = std::to_underlying(Permission::Read) + std::to_underlying(Permission::Execute);
    std::println("Read + Execute value: {}", perm_val);

}
