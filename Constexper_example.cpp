#include <iostream>

// Imagine you have a structure with three elements
struct CPerson {
    private:
    std::string name;
    int age;
    double height;
    public:
    CPerson(std::string n, int a, double h) : name(n), age(a), height(h) {}
    // Getter for Name
    std::string& getName() { return name; }
    // Getter for Age
    int& getAge() { return age; }
    // Getter for Height
    double& getHeight() { return height; }
};

// Now lets say, before c++17, u want to access the members of CPerson using templates
template <std::size_t I>
auto& get_old_style(CPerson& person);

template<>
auto& get_old_style<0>(CPerson& person) {
    return person.getName();
}

template<>
auto& get_old_style<1>(CPerson& person) {
    return person.getAge();
}

template<>
auto& get_old_style<2>(CPerson& person) {
    return person.getHeight();
}

// with c++17, this can be simplified using constexpr
template <std::size_t I>
auto& get(CPerson& person) {
    if constexpr (I == 0) return person.getName();
    else if constexpr (I == 1) return person.getAge();
    else if constexpr (I == 2) return person.getHeight();
    else static_assert(I < 3, "Invalid index");
}


int main() {
    CPerson person("John Doe", 30, 5.9);
    std::cout << "Old Style Access:" << std::endl;
    std::cout << "Name: " << get_old_style<0>(person) << std::endl;
    std::cout << "Age: " << get_old_style<1>(person) << std::endl;
    std::cout << "Height: " << get_old_style<2>(person) << std::endl;

    std::cout << "New Style Access:" << std::endl;
    std::cout << "Name: " << get<0>(person) << std::endl;
    std::cout << "Age: " << get<1>(person) << std::endl;
    std::cout << "Height: " << get<2>(person) << std::endl;

    return 0;
}
