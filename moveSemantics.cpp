#include <iostream>
#include <vector>

int main() {
    int a = 5;
    int b = 10;

    // Move semantics in action
    std::cout << "Before move: a = " << a << ", b = " << b << std::endl;

    b = std::move(a);

    std::cout << "After move: a = " << a << ", b = " << b << std::endl;

    // string
    std::string str1 = "Hello";
    std::string str2 = "World";

    std::cout << "Before move: str1 = " << str1 << ", str2 = " << str2 << std::endl;

    str2 = std::move(str1);

    std::cout << "After move: str1 = " << str1 << ", str2 = " << str2 << std::endl;

    // user defined data
    struct MyData {
        int value;
        MyData(int v) : value(v) {}
    };

    MyData data1(100);
    MyData data2(200);

    std::cout << "Before move: data1 = " << data1.value << ", data2 = " << data2.value << std::endl;

    data2 = std::move(data1);

    std::cout << "After move: data1 = " << data1.value << ", data2 = " << data2.value << std::endl;

    // user defined data types with pointer
    struct MyDataPtr {
        int* value;
        MyDataPtr(int v) : value(new int(v)) {}
        ~MyDataPtr() { delete value; }
    };

    MyDataPtr dataPtr1(100);
    MyDataPtr dataPtr2(200);

    std::cout << "Before move: dataPtr1 = " << *dataPtr1.value << ", dataPtr2 = " << *dataPtr2.value << std::endl;

    dataPtr2 = std::move(dataPtr1);

    std::cout << "After move: dataPtr1 = " << (dataPtr1.value ? *dataPtr1.value : 0) << ", dataPtr2 = " << *dataPtr2.value << std::endl;

    // Doing this through move semantics with Rule of 5 Implementation
    struct MyData_MoveSemantics {
        int* value;
        MyData_MoveSemantics(int v) : value(new int(v)) {}
        ~MyData_MoveSemantics() { delete value; }
        MyData_MoveSemantics(MyData_MoveSemantics&& other) noexcept : value(other.value) {
            other.value = nullptr;
        }
        MyData_MoveSemantics& operator=(MyData_MoveSemantics&& other) noexcept {
            if (this != &other) {
                delete value;
                value = other.value;
                other.value = nullptr;
            }
            return *this;
        }
    };

    MyData_MoveSemantics data1_ms(100);
    MyData_MoveSemantics data2_ms(200);

    std::cout << "Before move: data1_ms = " << *data1_ms.value << ", data2_ms = " << *data2_ms.value << std::endl;

    data2_ms = std::move(data1_ms);

    std::cout << "After move: data1_ms = " << (data1_ms.value ? *data1_ms.value : 0) << ", data2_ms = " << *data2_ms.value << std::endl;

    // vector handling
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    std::cout << "Before move: vec1 = ";
    for (const auto& v : vec1) std::cout << v << " ";
    std::cout << ", vec2 = ";
    for (const auto& v : vec2) std::cout << v << " ";
    std::cout << std::endl;

    vec2 = std::move(vec1);

    std::cout << "After move: vec1 = ";
    for (const auto& v : vec1) std::cout << v << " ";
    std::cout << ", vec2 = ";
    for (const auto& v : vec2) std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}