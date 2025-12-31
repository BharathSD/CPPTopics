#include <iostream>
#include <optional>
#include <string>
#include <vector>

std::optional<int> try_parse_int(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (...) {
        return std::nullopt;
    }
}

struct User {
    std::string name;
    int id;
};

std::optional<User> find_user_by_id(const std::vector<User>& users, int id) {
    for (const auto& user : users) {
        if (user.id == id) {
            return user;
        }
    }
    return std::nullopt;
}

std::optional<User> find_user_by_name(const std::vector<User>& users, const std::string& name) {
    for (const auto& user : users) {
        if (user.name == name) {
            return user;
        }
    }
    return std::nullopt;
}

int main() {
    // optional example
    std::optional<int> value = std::nullopt;

    if (value) {
        std::cout << "Value is: " << *value << std::endl;
    } else {
        std::cout << "Value is not set." << std::endl;
    }

    std::string input = "123abc";
    auto parsed_value = try_parse_int(input);

    if (parsed_value) {
        std::cout << "Parsed value is: " << *parsed_value << std::endl;
    } else {
        std::cout << "Failed to parse integer." << std::endl;
    }

    // another parser
    std::string another_input = "456";
    auto another_parsed_value = try_parse_int(another_input);

    if (another_parsed_value) {
        std::cout << "Parsed another value is: " << *another_parsed_value << std::endl;
    } else {
        std::cout << "Failed to parse another integer." << std::endl;
    }

    // another example usecase
    std::vector<User> users = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    if(auto user = find_user_by_id(users, 25)) {
        std::cout << "Found user: " << user->name << " with ID: " << user->id << std::endl;
    } else {
        std::cout << "User not found." << std::endl;
    }

    if(auto user = find_user_by_name(users, "Alice")) {
        std::cout << "Found user: " << user->name << " with ID: " << user->id << std::endl;
    } else {
        std::cout << "User not found." << std::endl;
    }


    // use value_or
    std::string user_name = find_user_by_id(users, 26).transform([](const User& user) {
        return user.name;
    }).value_or("Unknown");
    
    std::cout << "User name is: " << user_name << std::endl;

    return 0;
}