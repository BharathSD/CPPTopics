#include <stacktrace>
#include <print>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <source_location>

// ==================================================================
// EXAMPLE 1: Basic Stacktrace Capture
// ==================================================================

void function_c() {
    std::print("=== EXAMPLE 1: Basic Stacktrace ===\n");
    
    // Capture current stacktrace
    auto trace = std::stacktrace::current();
    
    std::print("Stack depth: {}\n", trace.size());
    std::print("\nFull stacktrace:\n{}\n\n", std::to_string(trace));
}

void function_b() {
    function_c();
}

void function_a() {
    function_b();
}

// ==================================================================
// EXAMPLE 2: Detailed Frame Inspection
// ==================================================================

void inspect_frames() {
    std::print("=== EXAMPLE 2: Frame-by-Frame Inspection ===\n");
    
    auto trace = std::stacktrace::current();
    
    std::print("Analyzing {} frames:\n\n", trace.size());
    
    for (size_t i = 0; i < trace.size(); ++i) {
        const auto& frame = trace[i];
        
        std::print("Frame {}:\n", i);
        std::print("  Description: {}\n", frame.description());
        std::print("  Source file: {}\n", frame.source_file());
        std::print("  Source line: {}\n", frame.source_line());
        std::print("  Native handle: {}\n\n", 
                   reinterpret_cast<void*>(frame.native_handle()));
    }
}

void caller_of_inspect() {
    inspect_frames();
}

// ==================================================================
// EXAMPLE 3: Custom Exception with Stacktrace
// ==================================================================

class DebugException : public std::exception {
    std::string message_;
    std::stacktrace trace_;
    
public:
    DebugException(std::string msg) 
        : message_(std::move(msg))
        , trace_(std::stacktrace::current(1))  // Skip constructor frame
    {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }
    
    const std::stacktrace& trace() const noexcept {
        return trace_;
    }
    
    std::string full_report() const {
        std::string report = "Exception: ";
        report += message_;
        report += "\n\nStacktrace:\n";
        report += std::to_string(trace_);
        return report;
    }
};

void risky_operation(int depth) {
    if (depth == 0) {
        throw DebugException("Critical failure at depth 0!");
    }
    risky_operation(depth - 1);
}

void safe_caller() {
    try {
        risky_operation(5);
    } catch (const DebugException& e) {
        std::print("=== EXAMPLE 3: Exception with Stacktrace ===\n");
        std::print("{}\n\n", e.full_report());
    }
}

// ==================================================================
// EXAMPLE 4: Partial Stacktrace (Skip/Max)
// ==================================================================

void deep_call_chain_5() {
    std::print("=== EXAMPLE 4: Partial Stacktrace ===\n");
    
    // Skip first 2 frames, max 5 frames
    auto trace = std::stacktrace::current(2, 5);
    
    std::print("Partial trace (skipped 2, max 5):\n");
    std::print("{}\n\n", std::to_string(trace));
}

void deep_call_chain_4() { deep_call_chain_5(); }
void deep_call_chain_3() { deep_call_chain_4(); }
void deep_call_chain_2() { deep_call_chain_3(); }
void deep_call_chain_1() { deep_call_chain_2(); }

// ==================================================================
// EXAMPLE 5: Performance Profiler with Stacktrace
// ==================================================================

#include <chrono>
#include <unordered_map>

class SimpleProfiler {
    struct ProfileData {
        size_t call_count = 0;
        std::chrono::microseconds total_time{0};
        std::stacktrace first_trace;
    };
    
    std::unordered_map<std::string, ProfileData> profiles_;
    
public:
    void record(const std::string& name, 
                std::chrono::microseconds duration,
                const std::stacktrace& trace) {
        auto& data = profiles_[name];
        data.call_count++;
        data.total_time += duration;
        if (data.call_count == 1) {
            data.first_trace = trace;
        }
    }
    
    void report() const {
        std::print("=== EXAMPLE 5: Profiling Report ===\n");
        for (const auto& [name, data] : profiles_) {
            std::print("\nFunction: {}\n", name);
            std::print("  Calls: {}\n", data.call_count);
            std::print("  Total time: {}μs\n", data.total_time.count());
            std::print("  Avg time: {}μs\n", 
                       data.total_time.count() / data.call_count);
            std::print("  First called from:\n");
            
            // Show where it was first called
            if (data.first_trace.size() > 1) {
                std::print("    {}\n", 
                           data.first_trace[1].description());
            }
        }
        std::print("\n");
    }
};

template<typename Func>
void profile_call(SimpleProfiler& profiler, 
                  const std::string& name, 
                  Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    auto trace = std::stacktrace::current();
    
    func();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start);
    
    profiler.record(name, duration, trace);
}

void expensive_operation_1() {
    // Simulate work
    volatile int sum = 0;
    for (int i = 0; i < 100000; ++i) sum += i;
}

void expensive_operation_2() {
    volatile int sum = 0;
    for (int i = 0; i < 50000; ++i) sum += i;
}

// ==================================================================
// EXAMPLE 6: Recursive Call Detection
// ==================================================================

class RecursionDetector {
    std::vector<std::string> seen_functions_;
    
public:
    bool check_recursion(const std::stacktrace& trace) {
        seen_functions_.clear();
        
        for (const auto& frame : trace) {
            std::string desc = frame.description();
            
            // Check if we've seen this function before
            for (const auto& seen : seen_functions_) {
                if (seen == desc) {
                    return true;  // Recursion detected!
                }
            }
            
            seen_functions_.push_back(desc);
        }
        
        return false;
    }
    
    void print_recursion_chain(const std::stacktrace& trace) {
        std::print("Recursion chain:\n");
        for (size_t i = 0; i < trace.size(); ++i) {
            std::print("  [{}] {}\n", i, trace[i].description());
        }
    }
};

void recursive_func(int depth, RecursionDetector& detector) {
    if (depth == 3) {
        auto trace = std::stacktrace::current();
        
        std::print("=== EXAMPLE 6: Recursion Detection ===\n");
        
        if (detector.check_recursion(trace)) {
            std::print("Recursion detected!\n");
            detector.print_recursion_chain(trace);
        }
        std::print("\n");
        return;
    }
    
    recursive_func(depth + 1, detector);
}

// ==================================================================
// EXAMPLE 7: Call Graph Builder
// ==================================================================

class CallGraph {
    struct Node {
        std::string function_name;
        std::vector<std::string> callers;
        size_t call_count = 0;
    };
    
    std::unordered_map<std::string, Node> graph_;
    
public:
    void record_call(const std::stacktrace& trace) {
        if (trace.size() < 2) return;
        
        // Current function
        std::string current = trace[0].description();
        
        // Caller
        std::string caller = trace[1].description();
        
        auto& node = graph_[current];
        node.function_name = current;
        node.call_count++;
        
        // Add caller if not already present
        bool found = false;
        for (const auto& c : node.callers) {
            if (c == caller) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            node.callers.push_back(caller);
        }
    }
    
    void print_graph() const {
        std::print("=== EXAMPLE 7: Call Graph ===\n");
        for (const auto& [name, node] : graph_) {
            std::print("\nFunction: {}\n", name);
            std::print("  Called {} times\n", node.call_count);
            std::print("  Callers:\n");
            for (const auto& caller : node.callers) {
                std::print("    - {}\n", caller);
            }
        }
        std::print("\n");
    }
};

CallGraph global_graph;

void monitored_func_a() {
    global_graph.record_call(std::stacktrace::current());
}

void monitored_func_b() {
    global_graph.record_call(std::stacktrace::current());
    monitored_func_a();
}

void monitored_func_c() {
    global_graph.record_call(std::stacktrace::current());
    monitored_func_a();
    monitored_func_b();
}

// ==================================================================
// EXAMPLE 8: Assertion with Context
// ==================================================================

#define DEBUG_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            auto trace = std::stacktrace::current(); \
            std::print("ASSERTION FAILED: {}\n", message); \
            std::print("Condition: {}\n", #condition); \
            std::print("Location: {}:{}\n", __FILE__, __LINE__); \
            std::print("\nStacktrace:\n{}\n", std::to_string(trace)); \
            std::terminate(); \
        } \
    } while(0)

void test_assertions(int value) {
    std::print("=== EXAMPLE 8: Assertions with Stacktrace ===\n");
    
    DEBUG_ASSERT(value > 0, "Value must be positive");
    std::print("Assertion passed for value = {}\n\n", value);
    
    // This would fail and show stacktrace:
    // DEBUG_ASSERT(value < 0, "This will fail");
}

// ==================================================================
// MAIN
// ==================================================================

int main() {
    // Example 1: Basic
    function_a();
    
    // Example 2: Frame inspection
    caller_of_inspect();
    
    // Example 3: Exception with trace
    safe_caller();
    
    // Example 4: Partial trace
    deep_call_chain_1();
    
    // Example 5: Profiler
    SimpleProfiler profiler;
    profile_call(profiler, "operation_1", expensive_operation_1);
    profile_call(profiler, "operation_2", expensive_operation_2);
    profile_call(profiler, "operation_1", expensive_operation_1);
    profiler.report();
    
    // Example 6: Recursion detection
    RecursionDetector detector;
    recursive_func(0, detector);
    
    // Example 7: Call graph
    monitored_func_c();
    monitored_func_b();
    global_graph.print_graph();
    
    // Example 8: Assertions
    test_assertions(42);
    
    return 0;
}