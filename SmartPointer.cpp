#include <iostream>
#include <memory>

int main() {
    // unique pointer
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::cout << "Value pointed by ptr1: " << *ptr1 << std::endl;

    std::unique_ptr<int> ptr2 = std::move(ptr1);
    std::cout << "Value pointed by ptr2: " << *ptr2 << std::endl;

    // shared pointer
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(42);
    std::cout << "Value pointed by sharedPtr1: " << *sharedPtr1 << std::endl;

    std::shared_ptr<int> sharedPtr2 = sharedPtr1;
    std::cout << "Value pointed by sharedPtr2: " << *sharedPtr2 << std::endl;

    sharedPtr1.reset();
    std::cout << "Value pointed by sharedPtr2 after sharedPtr1 reset: " << *sharedPtr2 << std::endl;

    // weak pointer
    /*
    A std::weak_ptr in C++ is a smart pointer that provides a non-owning reference 
    to an object managed by std::shared_ptr. Its main use is to break circular references 
    that can cause memory leaks when using shared_ptr. A weak_ptr does not affect the 
    reference count of the object. You can check if the object still exists and temporarily
    access it by converting the weak_ptr to a shared_ptr using the lock() method. 
    If the object has been deleted, lock() returns nullptr.
    */
    std::weak_ptr<int> weakPtr = sharedPtr2;
    if (auto lockedPtr = weakPtr.lock()) {
        if (lockedPtr) {
            std::cout << "Value pointed by weakPtr: " << *lockedPtr << std::endl;
        }
    }

    return 0;
}