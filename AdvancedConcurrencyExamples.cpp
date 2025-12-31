/*
This file demonstrates advanced C++ concurrency features with detailed explanations and examples.

1. std::shared_mutex and std::shared_lock
2. std::atomic
3. std::scoped_lock
4. std::latch and std::barrier (C++20)
5. std::thread::hardware_concurrency
6. Thread pool pattern
7. Parallel algorithms (C++17+)
8. std::jthread and std::stop_token (C++20)
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <numeric>
#include <algorithm>
#if __cpp_lib_latch
#include <latch>
#endif
#if __cpp_lib_barrier
#include <barrier>
#endif
#include <execution>
// #if __cpp_lib_jthread
// #include <stop_token>
// #include <jthread>
// #endif

// 1. std::shared_mutex and std::shared_lock
// Allows multiple readers or one writer at a time.
/*

A std::shared_mutex allows multiple threads to acquire a shared (read) lock simultaneously, 
but only one thread to acquire an exclusive (write) lock at a time. This is different from a 
regular std::mutex, which only allows one thread to lock it at any time, regardless of whether 
the thread is reading or writing.

Uses and advantages of shared_mutex over mutex:

- Greatly improves performance in scenarios with many readers and few writers, 
  as multiple threads can read shared data concurrently.
- Prevents write-write and read-write conflicts, ensuring data consistency.
- Useful for protecting resources that are frequently read but infrequently modified, 
  such as caches, configuration data, or lookup tables.
*/

void shared_mutex_example() {
    static int shared_data = 0;
    static std::shared_mutex smtx;
    auto reader = [] {
        std::shared_lock lock(smtx);
        std::cout << "Reader sees: " << shared_data << std::endl;
    };
    auto writer = [] {
        std::unique_lock lock(smtx);
        shared_data++;
        std::cout << "Writer updated data to: " << shared_data << std::endl;
    };
    std::thread t1(reader), t2(reader), t3(writer);
    t1.join(); t2.join(); t3.join();
}

// 2. std::atomic
// Provides lock-free, thread-safe operations on basic types.
/*
std::atomic in C++ is a template class that provides atomic (indivisible) operations on variables, 
ensuring thread safety without the need for explicit locks like std::mutex. Atomic operations are 
crucial in concurrent programming to prevent data races when multiple threads access and modify shared variables.

Key Features and Uses:
- Lock-Free Operations:
  std::atomic allows operations such as load, store, increment, decrement, and compare-and-swap to be 
  performed atomically, often using special CPU instructions. This can be much faster than using mutexes, 
  especially for simple data types.

- Thread Safety:
  All operations on an std::atomic variable are safe to use from multiple threads simultaneously. 
  For example, incrementing an atomic counter from several threads will always produce the correct result.

- Types Supported:
  std::atomic works with most fundamental types (int, bool, pointers, etc.) 
  and can be specialized for user-defined types that are trivially copyable.

- Common Use Cases:
  - Counters and flags shared between threads.
  - Reference counting (e.g., in smart pointers).
  - Implementing lock-free data structures.
  - Producer-consumer patterns.
*/
void atomic_example() {
    std::atomic<int> counter{0};
    auto increment = [&] {
        for (int i = 0; i < 1000; ++i) counter++;
    };
    std::thread t1(increment), t2(increment);
    t1.join(); t2.join();
    std::cout << "Atomic counter: " << counter << std::endl;
    std::cout << "Atomic counter (load): " << counter.load() << std::endl;
}

struct Point {
    int x;
    int y;
};

void userDefined_atomic_example() {
    // Mark Point as trivially copyable and suitable for atomic
    static_assert(std::is_trivially_copyable<Point>::value, "Point must be trivially copyable");

    std::atomic<Point> atomicPoint{Point{0, 0}};

    auto move_point = [&atomicPoint]() {
        for (int i = 0; i < 1000; ++i) {
            Point old = atomicPoint.load();
            Point next = {old.x + 1, old.y + 1};

            // Use compare_exchange_weak for atomic update
            while (!atomicPoint.compare_exchange_weak(old, next)) {
                next = {old.x + 1, old.y + 1};
            }
        }
    };

    std::thread t1(move_point), t2(move_point);
    t1.join(); t2.join();
    Point p = atomicPoint.load();
    std::cout << "Final position: (" << p.x << ", " << p.y << ")\n";

}

// 3. std::scoped_lock
// Locks multiple mutexes at once, preventing deadlocks.
/*
std::scoped_lock is a C++17 feature that provides a convenient and safe way to lock one or more 
mutexes at the same time. It is designed to prevent deadlocks and ensure exception safety when 
working with multiple mutexes.

Key Features and Uses:
- Multiple Mutex Locking:
  std::scoped_lock can lock several mutexes in a single statement, always using a deadlock-avoidance 
  algorithm (like std::lock internally). This is especially useful when you need to protect multiple 
  shared resources at once.

- RAII (Resource Acquisition Is Initialization):
  The mutexes are locked when the scoped_lock is created and automatically unlocked when it goes out of scope, 
  even if an exception is thrown. This ensures you never forget to unlock a mutex.

- Simplicity and Safety:
  It replaces older patterns like manually calling std::lock and then creating multiple std::lock_guard objects 
  with std::adopt_lock. scoped_lock is less error-prone and more readable.

*/
void scoped_lock_example() {
    std::mutex m1, m2;
    int a = 0, b = 0;
    auto worker = [&] {
        std::scoped_lock lock(m1, m2);
        a++; b++;
    };
    std::thread t1(worker), t2(worker);
    t1.join(); t2.join();
    std::cout << "a: " << a << ", b: " << b << std::endl;
}

// 4. std::latch and std::barrier (C++20)
/*
std::latch and std::barrier are synchronization primitives introduced in C++20 that simplify thread coordination.

- std::latch:
  A latch is a synchronization mechanism that allows one or more threads to wait until a certain condition 
  is met (i.e., until the latch is "released"). It is initialized with a count and can be decremented by 
  calling count_down(). When the count reaches zero, all waiting threads are unblocked.

- std::barrier:
  A barrier is a synchronization point where threads can wait until a certain number of them have reached 
  the barrier. It is initialized with a count and allows threads to arrive_and_wait() at the barrier. 
  Once the specified number of threads have arrived, they are all released to continue execution.

These primitives are useful for coordinating complex interactions between threads, such as ensuring that 
all threads have completed a certain phase of work before proceeding.

*/
#if __cpp_lib_latch
void latch_example() {
    std::latch done(3);
    auto worker = [&done] {
        std::cout << "Thread done\n";
        done.count_down();
    };
    std::thread t1(worker), t2(worker), t3(worker);
    t1.join(); t2.join(); t3.join();
    done.wait();
    std::cout << "All threads finished (latch)\n";
}
#endif
#if __cpp_lib_barrier
void barrier_example() {
    std::barrier sync_point(3);
    auto worker = [&sync_point] {
        std::cout << "Thread reached barrier\n";
        sync_point.arrive_and_wait();
        std::cout << "Thread passed barrier\n";
    };
    std::thread t1(worker), t2(worker), t3(worker);
    t1.join(); t2.join(); t3.join();
}
#endif

// 5. std::thread::hardware_concurrency
void hardware_concurrency_example() {
    unsigned n = std::thread::hardware_concurrency();
    std::cout << "Hardware concurrency: " << n << std::endl;
}

// 6. Thread pool pattern (simple)
#include <queue>
#include <functional>
#include <condition_variable>
class SimpleThreadPool {
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
public:
    SimpleThreadPool(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(mtx);
                        cv.wait(lock, [this]{ return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    void enqueue(std::function<void()> f) {
        {
            std::lock_guard lock(mtx);
            tasks.push(std::move(f));
        }
        cv.notify_one();
    }
    ~SimpleThreadPool() {
        {
            std::lock_guard lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto& t : workers) t.join();
    }
};
void thread_pool_example() {
    SimpleThreadPool pool(4);
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i]{ std::cout << "Task " << i << " done\n"; });
    }
}

// 7. Parallel algorithms (C++17+)
void parallel_algorithms_example() {
    std::vector<int> v(10000);
    std::iota(v.begin(), v.end(), 1);
    int sum = 0;
    std::for_each(std::execution::par, v.begin(), v.end(), [&](int x){ sum += x; });
    std::cout << "Parallel sum: " << sum << std::endl;
}

// 8. std::jthread and std::stop_token (C++20)
// #if __cpp_lib_jthread
// void jthread_example() {
//     auto work = [](std::stop_token st) {
//         while (!st.stop_requested()) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(100));
//             std::cout << "Working...\n";
//         }
//         std::cout << "Stopped!\n";
//     };
//     std::jthread jt(work);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     jt.request_stop();
//     jt.join();
// }
// #endif

int main() {
    std::cout << "1. shared_mutex/shared_lock example\n";
    shared_mutex_example();
    std::cout << "\n2. atomic example\n";
    atomic_example();
    std::cout << "\n2a. user-defined atomic example\n";
    userDefined_atomic_example();
    std::cout << "\n3. scoped_lock example\n";
    scoped_lock_example();
#if __cpp_lib_latch
    std::cout << "\n4. latch example\n";
    latch_example();
#endif
#if __cpp_lib_barrier
    std::cout << "\n4. barrier example\n";
    barrier_example();
#endif
    std::cout << "\n5. hardware_concurrency example\n";
    hardware_concurrency_example();
    std::cout << "\n6. thread pool example\n";
    thread_pool_example();
    std::cout << "\n7. parallel algorithms example\n";
    parallel_algorithms_example();
// #if __cpp_lib_jthread
//     std::cout << "\n8. jthread/stop_token example\n";
//     jthread_example();
// #endif
    return 0;
}
