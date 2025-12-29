#include <iostream>
#include <utility>

class ResourceHolder {
    int* data;
public:
    ResourceHolder(int value) : data(new int(value)) {}

    // Move constructor
    ResourceHolder(ResourceHolder&& other) noexcept
        : data(std::exchange(other.data, nullptr)) {}

    // Move assignment operator
    ResourceHolder& operator=(ResourceHolder&& other) noexcept {
        if (this != &other) {
            delete data;
            data = std::exchange(other.data, nullptr);
        }
        return *this;
    }

    ~ResourceHolder() { delete data; }

    int get() const { return data ? *data : 0; }
};

int main() {
    ResourceHolder a(42);
    ResourceHolder b = std::move(a); // Move constructor
    ResourceHolder c(100);
    c = std::move(b);                // Move assignment

    std::cout << "c: " << c.get() << std::endl; // 42
    std::cout << "a: " << a.get() << std::endl; // 0
    std::cout << "b: " << b.get() << std::endl; // 0

    return 0;
}