#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>
#include <chrono>
#include <random>


int main() {
    std::cout << "Hello, Parallel Algorithms!" << std::endl;

    std::vector<int> vec(1'000'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
    std::vector<int> vec_copy = vec;

    // normal sort
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::sort(vec.begin(), vec.end());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal sort took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel sort
    begin = std::chrono::steady_clock::now();
    std::sort(std::execution::par, vec_copy.begin(), vec_copy.end());
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel sort took: " << elapsed_ns << " ns" << std::endl;

    // lets do sum
    // Normal sum
    begin = std::chrono::steady_clock::now();
    auto sum = std::reduce(vec.begin(), vec.end(), 0);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal reduce (sum) took: " << elapsed_ns << " ns" << std::endl;


    // Parallel sum
    begin = std::chrono::steady_clock::now();
    sum = std::reduce(std::execution::par, vec_copy.begin(), vec_copy.end(), 0);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel reduce (sum) took: " << elapsed_ns << " ns" << std::endl;

    // normal for_each
    begin = std::chrono::steady_clock::now();
    std::for_each(vec.begin(), vec.end(), [](int& n) { n++; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal for_each took: " << elapsed_ns << " ns" << std::endl;

    // Parallel for_each
    begin = std::chrono::steady_clock::now();
    std::for_each(std::execution::par, vec_copy.begin(), vec_copy.end(), [](int& n) { n++; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel for_each took: " << elapsed_ns << " ns" << std::endl;

    // Normal transform
    begin = std::chrono::steady_clock::now();
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal transform took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel transform
    begin = std::chrono::steady_clock::now();
    std::transform(std::execution::par, vec_copy.begin(), vec_copy.end(), vec_copy.begin(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel transform took: " << elapsed_ns << " ns" << std::endl;


    // additional parallel operations can be added here
    // Normal find
    begin = std::chrono::steady_clock::now();
    auto it = std::find(vec.begin(), vec.end(), 500'000);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal find took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel find
    begin = std::chrono::steady_clock::now();
    auto it_p  = std::find(std::execution::par, vec_copy.begin(), vec_copy.end(), 500'000);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel find took: " << elapsed_ns << " ns" << std::endl;

    // Normal count
    begin = std::chrono::steady_clock::now();
    auto count = std::count(vec.begin(), vec.end(), 500'000);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal count took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel count
    begin = std::chrono::steady_clock::now();
    auto count_p = std::count(std::execution::par, vec_copy.begin(), vec_copy.end(), 500'000);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel count took: " << elapsed_ns << " ns" << std::endl;

    // Additional parallel operations can be added here
    // normal find
    begin = std::chrono::steady_clock::now();
    auto it = std::find(vec.begin(), vec.end(), 500'000);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal find took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel find
    begin = std::chrono::steady_clock::now();
    auto it_p  = std::find(std::execution::par, vec_copy.begin(), vec_copy.end(), 500'000);
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel find took: " << elapsed_ns << " ns" << std::endl;


    return 0;
}