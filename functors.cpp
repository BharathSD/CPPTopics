#include <format>
// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class MultBy {
    int factor;
public:
    MultBy(int f) : factor(f) {}
    int operator()(int x) const { return x * factor; }
};

// another functor example to append a suffix
class Append {
    std::string suffix;
public:
    Append(std::string s) : suffix(std::move(s)) {}
    std::string operator()(const std::string& str) const {
        return str + suffix;
    }
};


int main() {
    const MultBy times2(2);
    const MultBy times5(5);
    const MultBy times24(4);

    print("times2(3) = {}\n", times2(3));
    print("times5(5) = {}\n", times5(5));
    print("times24(12) = {}\n", times24(12));

    const Append appendExclamation("!");
    print("appendExclamation(\"Hello\") = {}\n", appendExclamation("Hello"));

    return 0;
}