#include <iostream>
#include <memory_resource>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>

/*
The usage of std::pmr::monotonic_buffer_resource is ideal for scenarios where you need a temporary, 
fast memory allocation strategy with a well-defined lifetime. It allocates memory from a fixed-size 
buffer and reclaims all memory at once when the buffer is reset or goes out of scope.
Whereas std::pmr::unsynchronized_pool_resource is better suited for scenarios with high allocation
churn, as it provides fast, low-friction memory allocation for small objects without the overhead
of tracking individual allocations.
whereas std::pmr::synchronized_pool_resource is designed for multi-threaded scenarios, providing
thread-safe memory allocation and deallocation.
*/

// Tiny timing helper
struct Timer {
    std::chrono::steady_clock::time_point t0{};
    void start() { t0 = std::chrono::steady_clock::now(); }
    double ms() const {
        auto t1 = std::chrono::steady_clock::now();
        return std::chrono::duration<double, std::milli>(t1 - t0).count();
    }
};

// 1) Request-scoped arena using monotonic_buffer_resource
void example_monotonic_arena() {
    std::cout << "\n[example_monotonic_arena]" << std::endl;

    std::byte buf[8 * 1024]; // 8KB local arena
    std::pmr::monotonic_buffer_resource arena{buf, sizeof(buf)};

    // PMR-aware types ensure all allocations come from the arena
    std::pmr::vector<std::pmr::string> words{&arena};
    words.reserve(128);

    for (int i = 0; i < 100; ++i) {
        words.emplace_back("item_" + std::to_string(i));
    }

    std::cout << "words size: " << words.size() << ", capacity: " << words.capacity() << std::endl;
    // Memory is reclaimed when 'arena' goes out of scope
}

// 2) Small-object churn with unsynchronized_pool_resource (single-threaded)
void example_pool_single_thread() {
    std::cout << "\n[example_pool_single_thread]" << std::endl;

    std::pmr::unsynchronized_pool_resource pool; // not thread-safe
    std::pmr::unordered_map<std::pmr::string, int> counts{&pool};

    for (int i = 0; i < 5000; ++i) {
        counts.emplace(std::pmr::string{"key_" + std::to_string(i), &pool}, i);
    }
    std::cout << "map size: " << counts.size() << std::endl;
}

// 3) Shared small-object pool across threads
void example_pool_multi_thread() {
    std::cout << "\n[example_pool_multi_thread]" << std::endl;

    std::pmr::synchronized_pool_resource sharedPool; // thread-safe
    auto worker = [&](int id) {
        std::pmr::vector<int> v{&sharedPool};
        for (int i = 0; i < 10000; ++i) v.push_back(id * 10000 + i);
        std::pmr::string s{&sharedPool};
        s = "thread_" + std::to_string(id);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        // v and s deallocate individually; pool manages blocks internally
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    t1.join();
    t2.join();

    std::cout << "workers done" << std::endl;
}

// 4) Custom tracking resource: wraps another resource and logs usage
struct TrackingResource : std::pmr::memory_resource {
    std::pmr::memory_resource* upstream;
    std::size_t allocatedBytes = 0;
    std::size_t deallocatedBytes = 0;

    explicit TrackingResource(std::pmr::memory_resource* up = std::pmr::get_default_resource())
        : upstream(up) {}

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        allocatedBytes += bytes;
        return upstream->allocate(bytes, alignment);
    }
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        deallocatedBytes += bytes;
        upstream->deallocate(p, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

void example_tracking_resource() {
    std::cout << "\n[example_tracking_resource]" << std::endl;

    std::pmr::monotonic_buffer_resource arena{1024};
    TrackingResource tracker{&arena};

    std::pmr::vector<std::pmr::string> v{&tracker};
    for (int i = 0; i < 50; ++i) v.emplace_back("str_" + std::to_string(i));

    std::cout << "allocated: " << tracker.allocatedBytes << " bytes, deallocated: "
              << tracker.deallocatedBytes << " bytes" << std::endl;
}

// 6) Small-object churn benchmark: unordered_map insert/erase
void example_small_object_churn() {
    std::cout << "\n[example_small_object_churn]" << std::endl;

    constexpr int N = 50000;
    auto make_key = [](int i) {
        // Short fixed-size key (~24 chars) to avoid SSO dominating
        std::string s = "k" + std::to_string(i);
        while (s.size() < 24) s.push_back('a');
        return s;
    };

    // Default unordered_map
    Timer tm; tm.start();
    {
        std::unordered_map<std::string, int> m;
        m.reserve(N);
        for (int i = 0; i < N; ++i) m.emplace(make_key(i), i);
        for (int i = 0; i < N; ++i) m.erase(make_key(i));
    }
    std::cout << "unordered_map<std::string> insert+erase: " << tm.ms() << " ms" << std::endl;

    // PMR unordered_map with unsynchronized_pool_resource
    std::pmr::unsynchronized_pool_resource pool;
    tm.start();
    {
        std::pmr::unordered_map<std::pmr::string, int> m{&pool};
        m.reserve(N);
        for (int i = 0; i < N; ++i) m.emplace(std::pmr::string{make_key(i), &pool}, i);
        for (int i = 0; i < N; ++i) m.erase(std::pmr::string{make_key(i), &pool});
    }
    std::cout << "pmr::unordered_map<pmr::string> (unsync pool) insert+erase: " << tm.ms() << " ms" << std::endl;
}

// 5) Quick comparison: default new/delete vs monotonic arena
void example_perf_compare() {
    std::cout << "\n[example_perf_compare]" << std::endl;

    constexpr int N = 50000;
    // Build a longer payload to bypass typical small-string optimization (SSO)
    auto make_payload = [](int i) {
        std::string base = "data_" + std::to_string(i) + "_";
        // target ~128 chars
        while (base.size() < 128) base += 'x';
        return base;
    };
    Timer tm;

    tm.start();
    {
        std::vector<std::string> v;
        v.reserve(N);
        for (int i = 0; i < N; ++i) v.emplace_back(make_payload(i));
    }
    std::cout << "std::vector<std::string> time: " << tm.ms() << " ms" << std::endl;

    // Allocate the large arena on the heap to avoid potential stack overflow
    std::vector<std::byte> buf(4 * 1024 * 1024);
    std::pmr::monotonic_buffer_resource arena{buf.data(), buf.size()};
    tm.start();
    {
        std::pmr::vector<std::pmr::string> v{&arena};
        v.reserve(N);
        for (int i = 0; i < N; ++i) v.emplace_back(make_payload(i));
    }
    std::cout << "std::pmr::vector<std::pmr::string> (arena) time: " << tm.ms() << " ms" << std::endl;

    // Add a pool resource case optimized for small allocations/deallocations
    std::pmr::unsynchronized_pool_resource pool;
    tm.start();
    {
        std::pmr::vector<std::pmr::string> v{&pool};
        v.reserve(N);
        for (int i = 0; i < N; ++i) v.emplace_back(make_payload(i));
    }
    std::cout << "std::pmr::vector<std::pmr::string> (unsync pool) time: " << tm.ms() << " ms" << std::endl;
}

int main() {
    // Disable auto line flush to reduce I/O noise in timing
    // std::cout.setf(std::ios::unitbuf);

    try { example_monotonic_arena(); }
    catch (const std::exception& e) { std::cerr << "example_monotonic_arena error: " << e.what() << std::endl; }

    try { example_pool_single_thread(); }
    catch (const std::exception& e) { std::cerr << "example_pool_single_thread error: " << e.what() << std::endl; }

    try { example_pool_multi_thread(); }
    catch (const std::exception& e) { std::cerr << "example_pool_multi_thread error: " << e.what() << std::endl; }

    try { example_tracking_resource(); }
    catch (const std::exception& e) { std::cerr << "example_tracking_resource error: " << e.what() << std::endl; }

    try { example_perf_compare(); }
    catch (const std::exception& e) { std::cerr << "example_perf_compare error: " << e.what() << std::endl; }

    try { example_small_object_churn(); }
    catch (const std::exception& e) { std::cerr << "example_small_object_churn error: " << e.what() << std::endl; }

    std::cout << "\nAll PMR examples done." << std::endl;
    
    return 0;
}
