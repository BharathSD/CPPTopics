#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <ranges>
#include <mutex>
#include <future>
#include <execution>

template <typename Range>
void parallelSum(Range range, int& result) {
    result = 0;
    for (auto&& v : range) {
        result += v;
    }
}

std::mutex mtx;

void print_id(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Function thread id: " << id << std::endl;
}

struct Functor {
    void operator()(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Functor thread id: " << id << std::endl;
    }
};

int main() {

    // simple thread creation
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = 0;


    std::thread t([&data, &sum] { parallelSum(data, sum); });
    t.join();
    std::cout << "Sum: " << sum << std::endl;

    // example with multiple threads
    int sum2 = 0;
    auto data2Process = data | std::views::filter([](int n) { return n % 2 == 0; });
    std::thread t2([data2Process, &sum2] { parallelSum(data2Process, sum2); });
    t2.join();
    std::cout << "Sum2: " << sum2 << std::endl;

    /*
    calling a function template like parallelSum directly in std::thread with automatic type
    deduction is not possible because the template parameters cannot be deduced from the context.
    This is why we use a lambda function to capture the necessary variables and explicitly specify
    the template parameters.
    */

    // complicated thread example
    std::vector<int> data3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum3 = 0;
    std::thread t3([&data3, &sum3] {
        for (auto&& v : data3) {
            sum3 += v;
        }
    });
    t3.join();
    std::cout << "Sum3: " << sum3 << std::endl;

    std::vector<std::thread> threads;

    // function pointer
    threads.emplace_back(print_id, 1);

    // lambda
    threads.emplace_back([](int id) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Lambda thread id: " << std::this_thread::get_id() << std::endl;
    }, 2);

    // functor
    threads.emplace_back(Functor(), 3);

    // passing reference to a variable
    int shared = 0;
    threads.emplace_back([&shared] {
        std::lock_guard<std::mutex> lock(mtx);
        shared = 42;
        std::cout << "Shared value set in thread : " << shared << std::endl;
    });

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final shared value: " << shared << std::endl;


    /*
    Using std::thread with move only types views and communicating via std::promise and std::future
    */
    // create a vector of 10 thousand integers and fill with some values
    std::vector<int> largeData(10000);
    // range operator to fill the vector with values
    std::iota(largeData.begin(), largeData.end(), 1);

    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t1([&largeData, &prom]() {
        auto even_members = largeData | std::views::filter([](int n) { return n % 2 == 0; });
        int sum = std::accumulate(even_members.begin(), even_members.end(), 0);
        prom.set_value(sum);
    });

    t1.join();

    std::cout << "Sum of largeData: " << fut.get() << std::endl;

    // another example with std::async
    std::future<int> fut2 = std::async([&largeData]() {
        auto odd_members = largeData | std::views::filter([](int n) { return n % 2 != 0; });
        return std::accumulate(odd_members.begin(), odd_members.end(), 0);
    });

    std::cout << "Sum of odd members: " << fut2.get() << std::endl;

    /*
    The main difference between std::async and std::thread in C++ 
    is how they manage asynchronous tasks and results:

    std::thread simply starts a new thread to run a function. 
    You must manually manage thread lifetime (e.g., call join() or detach()),
    and if you want to get a result from the thread, you need to use additional mechanisms 
    like std::promise and std::future.

    std::async both starts an asynchronous task and automatically manages its lifetime. 
    It returns a std::future that you can use to get the result of the task. When you call future.get(), 
    it waits for the task to finish and retrieves the result. std::async can run the task in a new thread 
    or defer execution, depending on the launch policy.
    */

    // another example of parallel for loop
    std::for_each(std::execution::par, largeData.begin(), largeData.end(), [](int& n) {
        n *= 2;
    });

    // another example of parallel for loop with std::transform
    std::vector<int> transformedData(largeData.size());
    std::transform(std::execution::par, largeData.begin(), largeData.end(), transformedData.begin(), [](int n) {
        return n * 2;
    });

    // another example of parallel for loop with std::reduce
    int totalSum = std::reduce(std::execution::par, largeData.begin(), largeData.end(), 0);
    std::cout << "Total sum: " << totalSum << std::endl;

    // another example with std::reduce
    int totalProduct = std::reduce(std::execution::par, largeData.begin(), largeData.end(), 1, std::multiplies<>());
    std::cout << "Total product: " << totalProduct << std::endl;

    // another example with std::reduce
    int totalMin = std::reduce(std::execution::par, largeData.begin(), largeData.end(), std::numeric_limits<int>::max(), [](int a, int b) { return std::min(a, b); });
    std::cout << "Total min: " << totalMin << std::endl;

    // another example with std::reduce
    int totalMax = std::reduce(std::execution::par, largeData.begin(), largeData.end(), std::numeric_limits<int>::min(), [](int a, int b) { return std::max(a, b); });
    std::cout << "Total max: " << totalMax << std::endl;

    // another example with std::reduce
    int totalCount = std::reduce(std::execution::par, largeData.begin(), largeData.end(), 0, [](int a, int b) { return a + 1; });
    std::cout << "Total count: " << totalCount << std::endl;

    // conditional variable example
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    std::thread worker([&]() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return ready; });
        std::cout << "Worker thread is processing data..." << std::endl;
    });

    // Simulate some work in the main thread
    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();

    worker.join();

    return 0;
}