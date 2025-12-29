#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>

int main() {
    int x = 42;
    auto lambda = [&]() { return x; };
    std::cout << lambda() << std::endl;

    // lambda example with STL
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::for_each(vec.begin(), vec.end(), [&](int n) { std::cout << n * 2 << " "; });
    std::cout << std::endl;

    // lambda example with std::bind
    auto sumLambda = [](int a, int b) { return a + b; };
    auto boundLambda = std::bind(sumLambda, std::placeholders::_1, 10);
    std::cout << boundLambda(32) << std::endl;

    // lambda example with std::function
    std::function<int(int, int)> func = sumLambda;
    std::cout << func(5, 10) << std::endl;

    // lambda example with capturing
    int y = 5;
    auto captureLambda = [y](int z) { return y + z; };
    std::cout << captureLambda(10) << std::endl;

    // lambda example with mutable
    int z = 5;
    auto mutableLambda = [z]() mutable { return z++; };
    std::cout << mutableLambda() << std::endl;
    std::cout << mutableLambda() << std::endl;

    // lambda example with generic
    auto genericLambda = [](auto a, auto b) { return a + b; };
    std::cout << genericLambda(5, 10) << std::endl;
    std::cout << genericLambda(5.5, 10.5) << std::endl;

    // lambda example with default arguments
    auto defaultLambda = [](int a, int b = 10) { return a + b; };
    std::cout << defaultLambda(5) << std::endl;

    // lambda used in sort
    std::vector<int> vec7 = {5, 2, 8, 1, 3};
    std::sort(vec7.begin(), vec7.end(), [](int a, int b) { return a > b; });
    for (int n : vec7) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // lambda used in remove_if
    std::vector<int> vec2 = {5, 2, 8, 1, 3};
    vec2.erase(std::remove_if(vec2.begin(), vec2.end(), [](int n) { return n < 3; }), vec2.end());
    for (int n : vec2) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    //lambda recursion example
    std::function<int(int)> factorial = [&](int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    };
    std::cout << factorial(5) << std::endl;

    // lambda example for fibonacci
    std::function<int(int)> fibonacci = [&](int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    };
    std::cout << fibonacci(5) << std::endl;

    // lambda example for quicksort
    std::vector<int> arr = {5, 2, 8, 1, 3};
    std::function<void(int, int)> quicksort = [&](int low, int high) {
        if (low < high) {
            int pivot = arr[high];
            int i = low - 1;
            for (int j = low; j < high; ++j) {
                if (arr[j] > pivot) {
                    std::swap(arr[++i], arr[j]);
                }
            }
            std::swap(arr[i + 1], arr[high]);
            quicksort(low, i);
            quicksort(i + 2, high);
        }
    };
    quicksort(0, arr.size() - 1);
    for (int n : arr) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // lambda example for binary search
    std::vector<int> sortedArr = {1, 2, 3, 4, 5};
    std::function<int(int)> binarySearch = [&](int target) {
        int low = 0;
        int high = sortedArr.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (sortedArr[mid] == target) return mid;
            if (sortedArr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    };
    std::cout << binarySearch(3) << std::endl;

    // lambda example for counting
    std::vector<int> vec6 = {1, 2, 3, 4, 5};
    int count = std::count_if(vec6.begin(), vec6.end(), [](int n) { return n % 2 == 0; });
    std::cout << count << std::endl;

    // lambda example for transforming
    std::vector<int> vec5 = {1, 2, 3, 4, 5};
    std::vector<int> transformed;
    std::transform(vec5.begin(), vec5.end(), std::back_inserter(transformed), [](int n) { return n * 2; });
    for (int n : transformed) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // lambda example for filtering
    std::vector<int> vec3 = {1, 2, 3, 4, 5};
    std::vector<int> filtered;
    std::copy_if(vec3.begin(), vec3.end(), std::back_inserter(filtered), [](int n) { return n % 2 == 0; });
    for (int n : filtered) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // lambda example for finding
    std::vector<int> vec4 = {1, 2, 3, 4, 5};
    auto it = std::find_if(vec4.begin(), vec4.end(), [](int n) { return n == 3; });
    if (it != vec4.end()) {
        std::cout << "Found: " << *it << std::endl;
    }

    return 0;
}