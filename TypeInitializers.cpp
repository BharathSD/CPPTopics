#include <iostream>
#include <typeinfo>
#include<vector>
//.
consteval int get_value(){
    return 3;
}

int main(){
    constexpr int value = get_value();
    std::cout << "value : " << value << std::endl;

    auto x = get_value();
    std::cout << "type of x : " << typeid(x).name() << std::endl;

    auto x2 = {1, 2, 3};
    std::cout << "type of x2 : " << typeid(x2).name() << std::endl;
    // Does not return a vector or array. it returns a std::initializer_list<int>

    auto x3 = 1.7;
    std::cout << "type of x3 : " << typeid(x3).name() << std::endl;

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "type of vec : " << typeid(vec).name() << std::endl;

    auto x4 = vec[0];
    std::cout << "type of x4 : " << typeid(x4).name() << std::endl;

    std::vector<bool> flags = {true, false, true};
    std::cout << "type of flags : " << typeid(flags).name() << std::endl;

    auto x5 = flags[0];
    std::cout << "type of x5 : " << typeid(x5).name() << std::endl;
    // Does not return a vector or array. it returns a std::vector<bool>::reference

    std::vector<std::string> words = {"hello", "world", "my love"};
    std::cout << "type of words : " << typeid(words).name() << std::endl;

    auto x6 = words[0];
    std::cout << "type of x6 : " << typeid(x6).name() << std::endl;

    auto x7 = 22;
    // of type int
    std::cout << "type of x7 : " << typeid(x7).name() << std::endl;

    auto x8 = {22};
    // of type std::initializer_list<int>
    std::cout << "type of x8 : " << typeid(x8).name() << std::endl;

    auto x9{22};
    // of type int
    std::cout << "type of x9 : " << typeid(x9).name() << std::endl;

    auto x10(22);
    // of type int
    std::cout << "type of x10 : " << typeid(x10).name() << std::endl;

    // auto x11{22,23,24}; // type cannot be deduced as it is confusing for the compiler

    // const and volatile decay
    const int ci = 42;
    auto x12 = ci;
    // of type int
    std::cout << "type of x12 : " << typeid(x12).name() << std::endl;
    x12 = 100; // can be modified because it is of type int

    const int& cref = ci;
    auto x13 = cref;
    // of type int
    std::cout << "type of x13 : " << typeid(x13).name() << std::endl;
    x13 = 100; // can be modified since it is of type int

    auto& x14 = ci;
    // of type const int
    std::cout << "type of x14 : " << typeid(x14).name() << std::endl;
    // x14 = 100; // error: assignment of read-only variable 'x14' as it is const int

    auto& x15 = cref;
    // of type const int&
    std::cout << "type of x15 : " << typeid(x15).name() << std::endl;

    // x15 = 100; // error: assignment of read-only location 'x15' as it is const int&

    const auto x16 = ci;
    // of type const int
    std::cout << "type of x16 : " << typeid(x16).name() << std::endl;

    // x16 = 100; // error: assignment of read-only variable 'x16' as it is const int

    const auto& x17 = ci;
    // of type const int&
    std::cout << "type of x17 : " << typeid(x17).name() << std::endl;
    // x17 = 100; // error: assignment of read-only location 'x17' as it is const int&

    const auto& x18 = cref;
    // of type const int&
    std::cout << "type of x18 : " << typeid(x18).name() << std::endl;   
    // x18 = 100; // error: assignment of read-only location 'x18' as it is const int&

    // pointer examples
    const int *ptr = &ci;
    // of type const int*
    std::cout << "type of ptr : " << typeid(ptr).name() << std::endl;

    auto x19 = ptr;
    // of type const int*
    std::cout << "type of x19 : " << typeid(x19).name() << std::endl;

    // way to get the decltype
    std::cout << "type of decltype((ci)) : " << typeid(decltype((ci))).name() << std::endl;

    // general confusing trait
    std::cout << (typeid(int).name() == typeid(const int).name()) << std::endl;

    // Difference between pointer to const and const pointer
    const int *ptr2 = &ci; // pointer to const int
    // *ptr2 = 10; // error: assignment of read-only location '*ptr2', this cannot be done as it is modifying the value
    const int value1 = 60;
    ptr2 = &value1; // valid, pointer can point to another address


    int *const ptr3 = &x10; // const pointer to int
    *ptr3 = 30; // valid, modifying the value at the address
    // ptr3 = &x11; // error: assignment of read-only variable 'ptr3' as it is const pointer

    // array types
    int a[5] = {1, 2, 3, 4, 5};
    std::cout << "type of a : " << typeid(a).name() << std::endl;

    auto a1 = a;
    // of type int[5]
    std::cout << "type of a1 : " << typeid(a1).name() << std::endl;
    *a1 = 25; // valid, modifying the first element

    auto a2 = std::begin(a);
    // of type int*
    std::cout << "type of a2 : " << typeid(a2).name() << std::endl;
    *a2 = 35; // valid, modifying the first element

    auto a3 = a[0];
    // of type int
    std::cout << "type of a3 : " << typeid(a3).name() << std::endl;
    a3 = 45; // valid, modifying the copy

    auto a4 = std::end(a);
    // of type int*
    std::cout << "type of a4 : " << typeid(a4).name() << std::endl;
    *a4 = 55; // valid, modifying the last element

    auto & a5 = a;
    // of type int (&)[5]
    std::cout << "type of a5 : " << typeid(a5).name() << std::endl;

    // sizeof trait
    std::cout << "size of a : " << sizeof(a) << std::endl; // size of the array
    std::cout << "size of a1 : " << sizeof(a1) << std::endl; // size of int*
    std::cout << "size of a2 : " << sizeof(a2) << std::endl; // size of int*
    std::cout << "size of a3 : " << sizeof(a3) << std::endl; // size of int
    std::cout << "size of a4 : " << sizeof(a4) << std::endl; // size of int*
    std::cout << "size of a5 : " << sizeof(a5) << std::endl; // size of int (&)[5]


    int b[10] = {};
    a1 = b; // valid, a1 is a pointer
    // a5 = b; // error: cannot assign to 'a5' because it is a reference of type int (&)[5]

    int c[5] = {};
    // a5 = c; // invalid, once the reference is bound to an array, it cannot be changed

    
    // forward reference or universal reference
    // Important note:
    // lvalue: an expression that refers to a memory location
    // rvalue: an expression that does not refer to a memory location

    // auto &z = 10; // error: cannot bind non-const lvalue reference to temporary
    const auto &z_c = 10; // valid, z_c is a const lvalue reference
    auto &&z = 10; // valid, z is an rvalue reference
    std::cout << "type of z : " << typeid(z).name() << std::endl;

    auto &&z1 = x7; // valid, x7 is an lvalue, so z1 is deduced to be int&
    std::cout << "type of z1 : " << typeid(z1).name() << std::endl;

    auto &&z2 = get_value(); // valid, get_value() is an rvalue, so z2 is deduced to be int&&
    std::cout << "type of z2 : " << typeid(z2).name() << std::endl;
    


    return 0;
}