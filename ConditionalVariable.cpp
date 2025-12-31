#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
int data = 0;

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        data = 42;
        ready = true;
        std::cout << "Producer: Data produced\n";
    }
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; }); // Wait until ready is true
    std::cout << "Consumer: Data received = " << data << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}