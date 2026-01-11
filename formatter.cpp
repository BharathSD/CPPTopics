#include <iostream>
#include <format>

struct Point2D {
    double x;
    double y;
};

template<>
struct std::formatter<Point2D> : std::formatter<std::string> {
    auto format(const Point2D& p, format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};

struct KeyValue {
    std::string key;
    std::string value;
};

template<>
struct std::formatter<KeyValue>  {
    char presentation = 'c';
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin();
        auto end = ctx.end();

        if (it != end && (*it == 'c' || *it == 'p')) {
            presentation = *it++;
        }
        if (it != end && *it != '}') {
            throw std::format_error("invalid format");
        }

        return it;

    }

    auto format(const KeyValue& kv, format_context& ctx) const {

        switch (presentation) {
            case 'p':
                return std::format_to(ctx.out(), "{} | {}", kv.key, kv.value);
            case 'c':
            default:
                return std::format_to(ctx.out(), "{} , {}", kv.key, kv.value);
        }
        return std::format_to(ctx.out(), "{} , {}", kv.key, kv.value);
    }
};

int main() {
    double val = 123.456789;
    std::cout << std::format("Default format: {}\n", val);
    std::cout << std::format("Fixed format: {:.2f}\n", val);
    std::cout << std::format("Scientific format: {:.2e}\n", val);
    std::cout << std::format("Hexadecimal format: {:a}\n", val);

    Point2D point{3.5, 7.2};
    std::cout << std::format("Point2D format: {}\n", point);

    KeyValue kv{"key", "value"};
    std::cout << std::format("KeyValue format (comma): {}\n", kv);
    std::cout << std::format("KeyValue format (pipe): {:p}\n", kv);

    return 0;
}