#include <iostream>
#include <variant>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <type_traits>


/*
Description: Demonstrating the use of std::variant in C++
std::variant can hold one of several types. it acts like a type-safe union.
the data can be accessed in a type-safe manner using std::visit or std::get or std::get_if
*/
// helper trait for dependent false
template<class>
struct always_false : std::false_type {};

template<unsigned N>
std::string repeat(std::string_view str) {
    std::string result;
    for (unsigned i = 0; i < N; ++i) {
        result += str;
    }
    return result;
}

// this is pre c++17 style of writing a visitor
template<unsigned N>
struct Multiplier_visitor_old {
    template<typename T>
    void operator()(T& value) const {
        value *= N;
    }
    void operator()(std::string& value) const {
        value = repeat<N>(value);
    }

    void operator()(std::array<int, 3>& arr) const {
        for (auto& v : arr) {
            v *= N;
        }
    }
};

// in c++17 or later, we can use constexpr if
template<unsigned N>
struct Multiplier_visitor {
    template<typename T>
    void operator()(T& value) const {
        if constexpr (std::is_arithmetic_v<T>) {
            value *= N;
        } else if constexpr (std::is_same_v<T, std::string>) {
            value = repeat<N>(value);
        } else if constexpr (std::is_same_v<T, std::array<int, 3>>) {
            for (auto& v : value) {
                v *= N;
            }
        }
        else {
            static_assert(always_false<T>::value, "Non-exhaustive visitor");
            // cannot use static_assert in a non-type context, hence the helper trait
        }
    }
};

// another visitor
struct Add_visitor {
    template<typename U>
    void operator()(U& value) const {
        if constexpr (std::is_arithmetic_v<U>) {
            value += value;
        } else if constexpr (std::is_same_v<U, std::string>) {
            value += value;
        } else if constexpr (std::is_same_v<U, std::array<int, 3>>) {
            for (auto& v : value) {
                v += v;
            }
        }
    }
};

// visitor for few data types
template<unsigned N>
struct Arithmetic_visitor {
    template<typename U>
    std::enable_if_t<std::is_arithmetic_v<U>, void>
    operator()(U& value) const {
        value *= N;
    }
};

template<unsigned N>
struct string_visitor {
    void operator()(std::string& value) const {
       value = repeat<N>(value);
    }
};

// helper trait using a language feature called variadic using declarations
template<unsigned N>
struct Visitor_helper : Arithmetic_visitor<N>, string_visitor<N> {
    using Arithmetic_visitor<N>::operator();
    using string_visitor<N>::operator();
};


// another example of variadic using declarations
/*
lets try and understand what is happening here.
- The below struct 'overload' inherits from all the (variadic) template parameters
- It also brings all their operator() overloads into the current scope using variadic using declarations
- Additionally we have added the deduction guide, so that it is quicker to instantiate the overload struct
- usage:
overload{Arithmetic_visitor<2>{}, string_visitor<2>{}}(value);
*/
template<typename... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};

// the deduction guide
template<typename... Ts>
overload(Ts...) -> overload<Ts...>;


int main()
{
    std::variant<int, std::string> var;

    var = 42;
    // visitor pattern
    std::visit([](auto&& arg) {
        std::cout << "Value: " << arg << std::endl;
    }, var);

    std::visit(Multiplier_visitor<2>{}, var);
    std::cout << "After multiplication/repetition: " << std::get<int>(var) << std::endl;

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

    std::visit(Multiplier_visitor<2>{}, var);
    std::cout << "After multiplication/repetition: " << std::get<std::string>(var) << std::endl;


    std::vector<std::variant<int, std::string>> vec = {42, "Hello, Variant!"};
    for (auto& v : vec) {
        std::visit(Visitor_helper<2>{}, v);
    }

    std::variant<int, std::string, std::array<int, 3>> v = 10;
    constexpr unsigned N = 3;
    auto overloader = overload{
        [](std::string& str) {str = repeat<N>(str);},
        [](std::array<int, 3>& arr) {
            for (auto& v : arr) {
                v *= N;
            }
        },
        [](int& t) { t *= N; }
    };

    std::visit(overloader, v);

    // changing the value
    v = std::array<int, 3>{1, 2, 3};
    std::visit(overloader, v);

    // change the value
    v = "42";
    std::visit(overloader, v);

    return 0;
}