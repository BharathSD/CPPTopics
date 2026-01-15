#include <print>
#include <mdspan>
#include <vector>
#include <print>
#include <numeric>

int main() {
    std::vector<int> vec(12);
    std::iota(vec.begin(), vec.end(), 1);
     // View data as contiguous memory representing 2 rows of 6 ints each
    auto ms2 = std::mdspan(vec.data(), 2, 6);
    // View the same data as a 3D array 2 x 3 x 2
    auto ms3 = std::mdspan(vec.data(), 2, 3, 2);

    // modify the data using ms2
   for (std::size_t i = 0; i != ms2.extent(0); i++)
        for (std::size_t j = 0; j != ms2.extent(1); j++)
            ms2[i, j] = i * 1000 + j;
    
    // Read back using 3D view
    for (std::size_t i = 0; i != ms3.extent(0); i++)
    {
        std::println("slice @ i = {}", i);
        for (std::size_t j = 0; j != ms3.extent(1); j++)
        {
            for (std::size_t k = 0; k != ms3.extent(2); k++)
                std::print("{:0>5} ", ms3[i, j, k]);
            std::println("");
        }
    }

    return 0;
}