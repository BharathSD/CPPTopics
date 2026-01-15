#include <iostream>
#include <expected>

// function returning std::expected
std::expected<int, std::string> may_fail() {
    return std::unexpected("Failure");
}

std::expected<int, std::string> divide(float numerator, float denominator) {
    if (denominator == 0) {
        return std::unexpected("Division by zero");
    }
    return numerator / denominator;
}

int main() {
    std::expected<int, std::string> result = may_fail();
    if (!result) {
        std::cerr << "Error: " << result.error() << std::endl;
    }

    auto division_result = divide(10.0f, 2.0f);
    if (!division_result) {
        std::cerr << "Error: " << division_result.error() << std::endl;
    } else {
        std::cout << "Division result: " << division_result.value() << std::endl;
    }

    // use transform and or_else
    auto doubled = division_result.transform([](float value) {
        return value * 2;
    });

    std::cout << "Doubled result: " << doubled.value() << std::endl;

    auto failed_result = divide(10.0f, 0.0f);
    if (!failed_result) {
        std::cerr << "Error: " << failed_result.error() << std::endl;
    }

    auto recovered = failed_result.or_else([](const std::string& err) {
    std::cout << "Recovering from error: " << err << std::endl;
    return std::expected<int, std::string>(0); // return expected, not int
});

    return 0;
}