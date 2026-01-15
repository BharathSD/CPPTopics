# CPPTopics

A curated collection of modern C++ examples, patterns, and features for quick reference and learning. Each file demonstrates a focused concept, from C++11 to C++23, with practical code and comments.

## Structure
- **Source files:** Each `.cpp` file covers a specific topic (e.g., lambdas, ranges, fold expressions, smart pointers, concurrency, type traits, bit manipulation, etc.).
- **build/**: Compiled executables (Debug)
- **build/release/**: Compiled executables (Release)
- **docs/**: Supplementary slides and PDFs for deeper dives

## Highlights
- **C++20/23 Features:** Ranges, concepts, `std::expected`, `std::print`, formatters, polymorphic memory resources, and more.
- **Classic Patterns:** Move semantics, perfect forwarding, variadic templates, type initializers, user-defined literals.
- **Concurrency:** Threading, condition variables, parallel algorithms.
- **Utilities:** Bit manipulation, fold expressions, container tricks.
- **Custom Formatters:** See `formatter.cpp`, `Rational.cpp` for C++20 formatting API usage.

## Build & Run
### Prerequisites
- Visual Studio 2022 or later (MSVC)
- C++20 or C++23 enabled

### Build (Debug)
Open any `.cpp` file and run the **Build with MSVC** task (Ctrl+Shift+B or via VS Code Tasks).

### Build (Release)
Open any `.cpp` file and run the **Build Release with MSVC** task.

### Run
After building, run the executable from PowerShell:
```powershell
./build/<filename>.exe
./build/release/<filename>.exe
```

## Notable Files
- `PolymorphicMemoryResources.cpp`: Practical PMR usage and benchmarks
- `Ranges_CPP20.cpp`: Modern range-based algorithms and views
- `FoldExpressions.cpp`: C++17 fold expressions in action
- `Rational.cpp`: Custom type with C++20 formatter
- `formatter.cpp`: Custom formatters for user types
- `expected_cpp23.cpp`: Error handling with `std::expected`
- `print_cpp23.cpp`: C++23 `std::print` and formatting

## Docs
- See `docs/` for slides and PDFs on advanced topics (move semantics, ranges, lambdas, etc.)

## Contributing
PRs welcome for new examples, bug fixes, or improved explanations. Please keep code concise and focused on a single concept per file.

## License
MIT
