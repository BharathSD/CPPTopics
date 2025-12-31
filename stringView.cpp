/*
std::string_view overview:
- Non-owning view into a contiguous character sequence. References existing data without copying.
- Header: <string_view>
- Benefits: zero-copy, easy slicing/subviews, works with literals/buffers, avoids temporary std::string.
- Core ops: size(), empty(), data(), operator[], substr(), remove_prefix(), remove_suffix(), find(), starts_with(), ends_with().
- Example: std::string_view line = "key=value"; auto pos = line.find('='); auto key = line.substr(0, pos); auto val = line.substr(pos + 1);
- Caveats: does not own memory; referenced data must outlive the view. Not guaranteed null-terminated; prefer size() over strlen.
- Use for read-only string parameters, efficient parsing/tokenization/logging.
*/
#include <iostream>
#include <string>
#include <string_view>

int main() {
    std::string str = "Hello, String View!";
    std::string_view strView = str;

    std::cout << "Original String: " << str << std::endl;
    std::cout << "String View: " << strView << std::endl;

    // More std::string_view use cases:
    // 1) Cheap slicing without allocations
    std::string_view sv = "key=value;count=42";
    auto eq = sv.find('=');
    std::string_view key = sv.substr(0, eq);
    std::string_view rest = sv.substr(eq + 1);
    auto sep = rest.find(';');
    std::string_view value = rest.substr(0, sep);
    std::cout << "key=" << key << ", value=" << value << std::endl;

    // 2) Trimming via remove_prefix/remove_suffix (in-place view adjustment)
    std::string_view trimDemo = "   padded   ";
    // left trim spaces
    auto firstNonSpace = trimDemo.find_first_not_of(' ');
    if (firstNonSpace != std::string_view::npos) trimDemo.remove_prefix(firstNonSpace);
    // right trim spaces
    auto lastNonSpace = trimDemo.find_last_not_of(' ');
    if (lastNonSpace != std::string_view::npos) trimDemo.remove_suffix(trimDemo.size() - (lastNonSpace + 1));
    std::cout << "trimmed='" << trimDemo << "'" << std::endl;

    // 3) Efficient function parameter (read-only)
    auto is_yes = [](std::string_view s) {
        return s == "yes" || s == "y" || s == "true";
    };
    std::cout << "is_yes('yes'): " << is_yes("yes") << std::endl;

    // 4) starts_with / ends_with for quick checks
    std::string_view path = "/api/v1/items";
    if (path.starts_with("/api/")) {
        std::cout << "API path: " << path << std::endl;
    }
    if (path.ends_with("items")) {
        std::cout << "Ends with 'items'" << std::endl;
    }

    // 5) Avoiding temporary std::string when logging literals or buffers
    const char* buf = "buffer-data";
    std::string_view bufView{buf, std::char_traits<char>::length(buf)};
    std::cout << "bufView: " << bufView << std::endl;

    return 0;
}