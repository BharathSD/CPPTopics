#include <iostream>
#include <vector>

template<typename Container>
auto getFirstValue(const Container& c){
    return c[0];
}

// since it is defined with decltype, the container returns reference type
/*
Here, decltype(c[1]) deduces the type exactly as the expression c[1] appears in the function parameter context.
For std::vector<int>, c[1] returns a reference to the element (specifically, const int& because c is a const Container&).
*/
template<typename Container>
auto getSecondValue(const Container& c) -> decltype(c[1]){
    return c[1];
}


int main() {
    std::vector<int> vec = {1, 2, 3};
    auto value = getFirstValue(vec);
    value *= 2;
    std::cout << value << std::endl;
    std::cout << vec[0] << std::endl; // should print 1 if return by value, 2 if return by reference

    auto value2 = getSecondValue(vec);
    value2 *= 2;
    std::cout << value2 << std::endl;
    std::cout << vec[1] << std::endl; // should print 2 if return by value, 4 if return by reference
    return 0;
}