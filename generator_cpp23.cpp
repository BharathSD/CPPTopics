#include <generator>
#include <print>
#include <ranges>
#include <vector>

namespace views = std::ranges::views;

/*
    ==================================================================
    WHY GENERATORS ARE POWERFUL

    1. LAZY EVALUATION:
       Infinite sequence only computes what you need:
         for (int val : infinite_counter(1000) | views::take(3)) { ... }

    2. MEMORY EFFICIENT:
       Generator doesn't store all values, just current state.
       fibonacci(1000000) doesn't allocate 1M integers!

    3. COMPOSABLE:
       Works seamlessly with ranges:
         auto composed = fibonacci(20)
                       | views::filter([](int x) { return x % 2 == 0; })
                       | views::take(5);

    4. READABLE:
       Complex iteration logic reads like sequential code.
       No manual iterator state management needed.
    ==================================================================
*/


// ==================================================================
// EXAMPLE 1: Basic Generator - Infinite Sequence
// ==================================================================

std::generator<int> infinite_counter(int start = 0) {
    while (true) {
        co_yield start++;  // Pause here, return value, resume on next iteration
    }
}

// ==================================================================
// EXAMPLE 2: Finite Generator - Fibonacci Sequence
// ==================================================================

std::generator<int> fibonacci(int count) {
    int a = 0, b = 1;
    
    for (int i = 0; i < count; ++i) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

// ==================================================================
// EXAMPLE 3: Generator with Custom Logic - Prime Numbers
// ==================================================================

std::generator<int> primes(int max) {
    auto is_prime = [](int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    };
    
    for (int n = 2; n <= max; ++n) {
        if (is_prime(n)) {
            co_yield n;
        }
    }
}

// ==================================================================
// EXAMPLE 4: Tree Traversal - Recursive Generator
// ==================================================================

struct TreeNode {
    int value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

std::generator<int> inorder_traversal(TreeNode* node) {
    if (!node) co_return;
    
    // Left subtree
    for (int val : inorder_traversal(node->left)) {
        co_yield val;
    }
    
    // Current node
    co_yield node->value;
    
    // Right subtree
    for (int val : inorder_traversal(node->right)) {
        co_yield val;
    }
}

// ==================================================================
// EXAMPLE 5: Combining Generators with Ranges
// ==================================================================

std::generator<int> range_generator(int start, int end, int step = 1) {
    for (int i = start; i < end; i += step) {
        co_yield i;
    }
}

// ==================================================================
// EXAMPLE 6: Generator with State - Running Statistics
// ==================================================================

struct Stats {
    double value;
    double running_avg;
    int count;
};

std::generator<Stats> running_average(const std::vector<double>& data) {
    double sum = 0.0;
    int count = 0;
    
    for (double val : data) {
        sum += val;
        count++;
        co_yield Stats{val, sum / count, count};
    }
}

// ==================================================================
// EXAMPLE 7: Lazy File Line Reader (Conceptual)
// ==================================================================

std::generator<std::string> read_lines(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        // In real implementation, this would read from file on-demand
        co_yield line;
    }
}

// ==================================================================
// MAIN - Demonstrate All Examples
// ==================================================================

int main() {
    std::print("=== EXAMPLE 1: Infinite Counter (first 5) ===\n");
    for (int val : infinite_counter(100) | views::take(5)) {
        std::print("{} ", val);
    }
    std::print("\n\n");
    
    std::print("=== EXAMPLE 2: Fibonacci (first 10) ===\n");
    for (int val : fibonacci(10)) {
        std::print("{} ", val);
    }
    std::print("\n\n");
    
    std::print("=== EXAMPLE 3: Primes up to 50 ===\n");
    for (int val : primes(50)) {
        std::print("{} ", val);
    }
    std::print("\n\n");
    
    std::print("=== EXAMPLE 4: Tree Inorder Traversal ===\n");
    // Build a simple tree:
    //       4
    //      / \
    //     2   6
    //    / \ / \
    //   1  3 5  7
    TreeNode n1{1}, n3{3}, n5{5}, n7{7};
    TreeNode n2{2, &n1, &n3};
    TreeNode n6{6, &n5, &n7};
    TreeNode root{4, &n2, &n6};
    
    for (int val : inorder_traversal(&root)) {
        std::print("{} ", val);
    }
    std::print("\n\n");
    
    std::print("=== EXAMPLE 5: Range Generator with Views ===\n");
    auto filtered = range_generator(0, 20, 2)  // Even numbers 0-20
                  | views::filter([](int x) { return x > 5; })
                  | views::transform([](int x) { return x * x; });
    
    for (int val : filtered) {
        std::print("{} ", val);
    }
    std::print("\n\n");
    
    std::print("=== EXAMPLE 6: Running Average ===\n");
    std::vector<double> data = {10.0, 20.0, 30.0, 40.0, 50.0};
    
    for (const auto& stat : running_average(data)) {
        std::print("Value: {:.1f}, Avg: {:.2f}, Count: {}\n", 
                   stat.value, stat.running_avg, stat.count);
    }
    std::print("\n");
    
    std::print("=== EXAMPLE 7: Lazy Line Reading ===\n");
    std::vector<std::string> file_lines = {
        "Line 1: Hello",
        "Line 2: World",
        "Line 3: From",
        "Line 4: Generator"
    };
    
    for (const auto& line : read_lines(file_lines) | views::take(2)) {
        std::print("{}\n", line);
    }
    std::print("\n");
    
        
    return 0;
}