#include <iostream>

constexpr long double operator"" _km(long double val) {
    return val * 1000.0;
}

constexpr long double operator"" _m(long double val) {
    return val;
}

constexpr long double operator"" _cm(long double val) {
    return val / 100.0;
}
constexpr long double operator"" _mm(long double val) {
    return val / 1000.0;
}

int main() {
    auto distance1 = 5.0_km;
    auto distance2 = 300.0_m;
    auto distance3 = 150.0_cm;
    auto distance4 = 75.0_mm;

    std::cout << "Distance 1: " << distance1 << " meters\n";
    std::cout << "Distance 2: " << distance2 << " meters\n";
    std::cout << "Distance 3: " << distance3 << " meters\n";
    std::cout << "Distance 4: " << distance4 << " meters\n";

    return 0;
}