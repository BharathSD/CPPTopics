#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>
#include <chrono>
#include <random>

 /*
    Description of all execution policies:
    - std::execution::seq: Sequential execution on a single thread.
    - std::execution::par: Parallel execution, potentially utilizing multiple threads.
    - std::execution::par_unseq: Parallel execution with vectorization support.
    - std::execution::unseq: Sequential execution with vectorization support.

    
    The difference between std::execution::par and std::execution::seq is that
    std::execution::par allows the algorithm to be executed in parallel, potentially
    utilizing multiple threads, while std::execution::seq enforces sequential execution
    on a single thread.

    The difference between std::execution::par and std::execution::par_unseq is that
    std::execution::par_unseq allows for both parallel execution and vectorization,
    potentially improving performance on certain workloads.

    Usage of the execution policies can be done by passing them as the first argument
    to the parallel algorithms. For example, to use parallel execution with
    std::transform, you can do the following:

    std::transform(std::execution::par, vec.begin(), vec.end(), result.begin(), [](int n) {
        return n * 2;
    });

    The choice of execution policy can have a significant impact on performance,
    especially for large datasets or computationally intensive tasks. It's important
    to choose the right policy based on the specific use case and the characteristics
    of the data being processed.

    Some algorithms may not benefit from parallel execution, especially if they involve
    a lot of inter-thread communication or if the workload is not large enough to
    justify the overhead of parallelism. In such cases, a sequential execution policy
    may be more efficient.

*/

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

    // example usage of transform_reduce
    begin = std::chrono::steady_clock::now();
    auto result = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal transform_reduce took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel transform_reduce
    begin = std::chrono::steady_clock::now();
    auto result_p = std::transform_reduce(std::execution::par, vec_copy.begin(), vec_copy.end(), 0, std::plus<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel transform_reduce took: " << elapsed_ns << " ns" << std::endl;

    // example usage of transform_inclusive_scan
    /*
    Description : transform_inclusive_scan applies a transformation to each element in a range and 
    then performs an inclusive scan (prefix sum) on the transformed elements.
    The difference between transform_reduce and transform_inclusive_scan is that
    transform_reduce combines all elements into a single value, while
    transform_inclusive_scan produces a new range of the same size as the input,
    where each element is the result of the transformation and the inclusive scan.
    in other words, the output range is built incrementally, with each element
    depending on the previous ones.
    Example:
    if the vector contains {1, 2, 3, 4}, the result of the inclusive scan will be {1, 3, 6, 10}.
    */
    begin = std::chrono::steady_clock::now();
    std::vector<int> inclusive_scan_result(vec.size());
    std::transform_inclusive_scan(vec.begin(), vec.end(), inclusive_scan_result.begin(), 0, std::plus<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal transform_inclusive_scan took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel transform_inclusive_scan
    begin = std::chrono::steady_clock::now();
    std::vector<int> inclusive_scan_result_p(vec_copy.size());
    std::transform_inclusive_scan(std::execution::par, vec_copy.begin(), vec_copy.end(), inclusive_scan_result_p.begin(), 0, std::plus<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel transform_inclusive_scan took: " << elapsed_ns << " ns" << std::endl;

    // example usage of transform_inclusive_scan with product
    begin = std::chrono::steady_clock::now();
    std::vector<int> inclusive_scan_result_prod(vec.size());
    std::transform_inclusive_scan(vec.begin(), vec.end(), inclusive_scan_result_prod.begin(), 1, std::multiplies<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal transform_inclusive_scan with product took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel transform_inclusive_scan with product
    begin = std::chrono::steady_clock::now();
    std::vector<int> inclusive_scan_result_prod_p(vec_copy.size());
    std::transform_inclusive_scan(std::execution::par, vec_copy.begin(), vec_copy.end(), inclusive_scan_result_prod_p.begin(), 1, std::multiplies<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel transform_inclusive_scan with product took: " << elapsed_ns << " ns" << std::endl;

    // example usage of transform_exclusive_scan
    /*
    Description: transform_exclusive_scan applies a transformation to each element in a range and 
    then performs an exclusive scan (prefix sum) on the transformed elements.
    The difference between transform_exclusive_scan and transform_inclusive_scan is that
    transform_exclusive_scan does not include the last element in the scan.
    */
    begin = std::chrono::steady_clock::now();
    std::vector<int> exclusive_scan_result(vec.size());
    std::transform_exclusive_scan(vec.begin(), vec.end(), exclusive_scan_result.begin(), 0, std::plus<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Normal transform_exclusive_scan took: " << elapsed_ns << " ns" << std::endl;

    // Example: Parallel transform_exclusive_scan
    begin = std::chrono::steady_clock::now();
    std::vector<int> exclusive_scan_result_p(vec_copy.size());
    std::transform_exclusive_scan(std::execution::par, vec_copy.begin(), vec_copy.end(), exclusive_scan_result_p.begin(), 0, std::plus<>(), [](int n) { return n * 2; });
    end = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Parallel transform_exclusive_scan took: " << elapsed_ns << " ns" << std::endl;

    // transform_reduce to perform dot product of two vectors
    std::vector<double> vec_a(10);
    std::iota(vec_a.begin(), vec_a.end(), 1.0);
    std::vector<double> vec_b(10);
    std::iota(vec_b.begin(), vec_b.end(), 1.0);
    // transform_reduce to perform dot product of two vectors
    double dot_product = std::transform_reduce(vec_a.begin(), vec_a.end(), vec_b.begin(), 0.0,
                            std::plus<>(), std::multiplies<>());

    std::cout << "Dot product: " << dot_product << std::endl;

    // parallel transform_reduce to perform dot product of two vectors
    double dot_product_par = std::transform_reduce(std::execution::par, vec_a.begin(), vec_a.end(), vec_b.begin(), 0.0,
                            std::plus<>(), std::multiplies<>());

    std::cout << "Parallel Dot product: " << dot_product_par << std::endl;

    // Norm  operation on the vector
    double norm = std::sqrt(std::transform_reduce(vec_a.begin(), vec_a.end(), 0.0,
                            std::plus<>(), [](double x) { return x * x; }));

    std::cout << "Norm: " << norm << std::endl;

    // parallel Norm operation on the vector
    double norm_par = std::sqrt(std::transform_reduce(std::execution::par, vec_a.begin(), vec_a.end(), 0.0,
                            std::plus<>(), [](double x) { return x * x; }));

    std::cout << "Parallel Norm: " << norm_par << std::endl;

   

    return 0;
}