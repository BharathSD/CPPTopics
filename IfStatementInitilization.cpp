#include <iostream>
#include <map>

auto get_value(const std::map<std::string, int>& myMap, const std::string& key) {
    if (auto it = myMap.find(key); it != myMap.end()) {
        return it->second;
    }
    return -1;  // Meaningful value indicating not found
}

int main() {
    // create a map
    std::map<std::string, int> myMap;
    myMap["apple"] = 1;
    myMap["banana"] = 2;
    myMap["orange"] = 3;

    if(auto it = myMap.find("banana"); it != myMap.end()) {
        std::cout << "Found banana: " << it->second << std::endl;
    }
    else if(it = myMap.find("grape"); it != myMap.end()) {
        std::cout << "Found grape: " << it->second << std::endl;
    }
    else {
        std::cout << "Neither banana nor grape found." << std::endl;
    }

    std::cout << "Switch statement:" << std::endl;

    switch (auto value = get_value(myMap, "orange"); value)
    {
    case 1:
        std::cout << "Found apple: " << value << std::endl;
        break;

    case 2:
        std::cout << "Found banana: " << value << std::endl;
        break;
    case 3:
        std::cout << "Found orange: " << value << std::endl;
        break;
    
    default:
        std::cout << "Neither apple, banana, nor orange found." << std::endl;
        break;
    }

    return 0;
}