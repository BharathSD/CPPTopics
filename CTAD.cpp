#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <string_view>

template<typename T, T v>
struct Constant_old {
   static constexpr T value = v;
};

// template <std::size_t N>
// Constant_old(const char (&)[N]) -> Constant_old<std::string_view, std::string_view>;


template<auto v>
struct Constant {
   static constexpr auto value = v;
};

template<typename T, T... elements>
struct Sequence_old {};

template<auto... elements>
struct Sequence {};



int main() {
    std::pair t(1, 4.5);
    std::cout << "Type of t: " << typeid(t).name() << std::endl;

    std::vector data{1,2,5,7,8};
    std::cout << "type of data: " << typeid(data).name() << std::endl;

    std::mutex mtx;
    std::lock_guard lock(mtx);
    std::cout << "type of mtx: " << typeid(mtx).name() << std::endl;
    std::cout << "type of lock: " << typeid(lock).name() << std::endl;

    using i_old = Constant_old<int, 5>;
    using i_new = Constant<5>;

    using f_old = Constant_old<float, 3.14f>;
    using f_new = Constant<3.14f>;

    using c_old = Constant_old<char, 'A'>;
    using c_new = Constant<'A'>;

    using d_old = Constant_old<double, 2.71828>;
    using d_new = Constant<2.71828>;

    using idxs_old = Sequence_old<int, 1, 2, 3>;
    using idxs_new = Sequence<1, 2, 3>;

    using str_old = Sequence_old<char, 'H', 'e', 'l', 'l', 'o'>;
    using str_new = Sequence<'H', 'e', 'l', 'l', 'o'>;

    std::cout << "i_old: " << i_old::value << ", i_new: " << i_new::value << std::endl;
    std::cout << "f_old: " << f_old::value << ", f_new: " << f_new::value << std::endl;
    std::cout << "c_old: " << c_old::value << ", c_new: " << c_new::value << std::endl;
    std::cout << "d_old: " << d_old::value << ", d_new: " << d_new::value << std::endl;

    auto add = [](int n, int m) {
        return n + m;
    };

    constexpr auto result = add(3, 4); // this works with c++17 or later.
    /*
    By default, lambdas are constexpr in C++17 and later. So you need not add constexpr in the signature.
    auto add = [](int n, int m) constexpr {
        return n + m;
    };

    */

    return 0;
}