#include <iostream>
#include <tuple>

// Helper to print tuple elements
template<std::size_t I = 0, typename... Tp>
void print_tuple_impl(const std::tuple<Tp...>& t, std::ostream& os) {
    if constexpr (I < sizeof...(Tp)) {
        if constexpr (I > 0) os << ", ";
        os << std::get<I>(t);
        print_tuple_impl<I + 1>(t, os);
    }
}

// Overload operator<< for tuples
template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
    os << "[";
    print_tuple_impl(t, os);
    os << "]";
    return os;
}

template<typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void print(const T& value, const Args&... args) {
    std::cout << value << " ";
    print(args...);
}


// extend to also print tuples
template<typename... Args>
void print(const std::tuple<Args...>& t) {
    std::cout << "[";
    print_tuple(t);
    std::cout << "]" << std::endl;
}

int main() {
    print(1, 2.5, "Hello", 'c');
    std::tuple<int, double, std::string, char> myTuple(1, 2.5, "Hello", 'c');
    std::cout << sizeof(myTuple) << std::endl;
    return 0;
}
