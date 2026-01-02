#include <iostream>
#include <type_traits>

/*
Conjunction is used to combine multiple type traits into a single boolean value.
it is better to use conjunction over the logical AND operator (&&) because it short-circuits
and can work with more than two operands.
short circuiting means that if the first operand is false, the second operand is not evaluated.
*/

/*
The difference between std::conjunction and std::disjunction is that conjunction requires all traits to be true,
while disjunction requires at least one trait to be true.
*/

// helper to check if all the template paramters are constructible
template <typename... Args>
using are_default_constructible = std::conjunction<std::is_default_constructible<Args>...>;

template <typename... Args>
constexpr bool are_default_constructible_v = are_default_constructible<Args...>::value;

template<class T>
using is_arithmetic_nonconst = std::conjunction<std::is_arithmetic<T>, std::negation<std::is_const<T>>>;

template<class T>
using is_arithmetic_nonconst_v = is_arithmetic_nonconst<T>::value;

template<class T>
using is_sequence_container = std::conjunction<
    std::is_same<typename T::value_type, typename T::allocator_type::value_type>,
    std::is_constructible<T, typename T::allocator_type>,
    std::is_default_constructible<T>,
    std::is_copy_constructible<T>,
    std::is_move_constructible<T>
>;

// example function using enable_if
template<typename T>
std::enable_if_t<
    std::conjunction<
        std::is_arithmetic<T>,
        std::is_nothrow_copy_constructible<T>
    >::value, T> 
    safe_add(T a, T b) noexcept {
    return a + b;
}

template<class T, class = void>
struct has_size : std::false_type {};

template<class T>
struct has_size<T, std::void_t<decltype(std::declval<T&>().size())>> : std::true_type {};

/*
std::declval is a utility function that creates a rvalue reference to a type T without actually constructing
an object of that type. It is often used in conjunction with std::void_t to detect the presence of 
certain member functions or types.

std::void_t is a utility type that produces a void type if all of its template arguments are valid, 
and it produces an invalid type otherwise. It is often used in SFINAE (Substitution Failure Is Not An Error) 
contexts to detect the presence of certain types or expressions.
*/
template<class T, class = void>
struct has_data : std::false_type {};

template<class T>
struct has_data<T, std::void_t<decltype(std::declval<T&>().data())>> : std::true_type {};

template<typename T>
using has_data_size = std::conjunction<has_size<T>, has_data<T>>;


int main() {
    static_assert(std::conjunction_v<std::is_integral<int>, std::is_signed<int>>, "int is not a signed integral type");
    static_assert(!std::conjunction_v<std::is_integral<int>, std::is_signed<unsigned int>>, "unsigned int is a signed integral type");

    // are_default_constructible<Ts...> is a trait type; use ::value to get the bool
    static_assert(are_default_constructible<std::string, const char*, std::size_t>::value,
                  "All listed types must be default-constructible");
    
    static_assert(are_default_constructible_v<std::string, int>,
                    "All listed types must be default-constructible");

    // If you want to check that std::string is constructible from (const char*, size_t), use is_constructible
    static_assert(std::conjunction_v<std::is_constructible<std::string, const char*, std::size_t>>, 
                  "std::string should be constructible from (const char*, size_t)");
    
    // -------- std::disjunction examples (logical OR of traits) --------
    // Basic: true if any trait is true
    static_assert(std::disjunction_v<std::is_integral<int>, std::is_floating_point<int>>);
    static_assert(!std::disjunction_v<std::is_pointer<int>, std::is_const<int>>);

    // Enable only if T is integral OR floating-point
    auto is_number_trait = []<class T>() {
        return std::disjunction_v<std::is_integral<T>, std::is_floating_point<T>>;
    };
    static_assert(is_number_trait.operator()<int>());
    static_assert(is_number_trait.operator()<double>());
    static_assert(!is_number_trait.operator()<std::string>());

    // Parameter-pack: any of Ts is const?
    template<class... Ts>
    struct any_const : std::disjunction<std::is_const<Ts>...> {};
    static_assert(any_const<const int, double, char>::value);
    static_assert(!any_const<int, double, char>::value);

    // Combine disjunction with negation: any type is nothrow move constructible OR trivially copyable
    template<class T>
    using movable_or_trivial = std::disjunction<std::is_nothrow_move_constructible<T>, std::is_trivially_copyable<T>>;
    static_assert(movable_or_trivial<int>::value);
    static_assert(movable_or_trivial<std::string>::value);

    
    
    return 0;
}