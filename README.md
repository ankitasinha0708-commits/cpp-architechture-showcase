# cpp-architechture-showcase
Small project to showcase Cpp architechtures

# C++ Enterprise PLM Architecture Showcase

A production-grade, headless C++20 architectural blueprint showcasing clean-code principles, decoupled design patterns, and asynchronous background processing. This project serves as a highly scalable engine design optimized to interface with enterprise Product Lifecycle Management (PLM) layers like **PTC Windchill**.

---

## Architectural Core Pillars

This repository acts as an architectural showcase demonstrating the core software engineering patterns required to lead enterprise-level desktop or backend C++ systems:

*   **Interface Abstraction & Decoupling:** Core execution logic communicates strictly through an abstract interface (`IPlmConnector`). The core engine has zero awareness of underlying network protocols, database layers, or third-party HTTP stacks.
*   **Dependency Injection (DI):** Engine component lifecycles are managed cleanly via modern C++ memory routines. Concrete connectors are safely injected into orchestrators using smart pointers (`std::unique_ptr` and `std::shared_ptr`), completely avoiding hidden singletons or global state tracking.
*   **Asynchronous Task Scheduling:** Implements a thread-safe, high-performance producer-consumer task queue manager leveraging **C++20 `std::jthread`** and `std::condition_variable_any`. It supports cooperative cancellation via `std::stop_token` to ensure rapid, deadlock-free system shutdowns.
*   **Automated Verification Framework:** Driven by **Google Test (GTest) and Google Mock** to guarantee structural edge-case protection, null-dependency assertions, and clean mock routing validation.

---

## Repository Structural Mapping

The project follows a standard, highly scannable production layout:

```text
+-- client/
¦   +-- main.cpp                  # Production simulation application entry point
+-- include/
¦   +-- core/
¦       +-- IPlmConnector.hpp     # Abstract interface definition (System Contract)
¦       +-- PlmClient.hpp         # Primary processing business logic orchestrator
¦       +-- AsyncPlmScheduler.hpp # Thread-safe C++20 background task queue manager
+-- src/
¦   +-- core/
¦       +-- PlmClient.cpp         # Synchronous processing implementation pipelines
¦       +-- AsyncPlmScheduler.cpp # Multi-threaded background worker execution loop
+-- tests/
¦   +-- test_main.cpp             # GTest verification test suites & mock pipelines
+-- .gitignore                    # Comprehensive exclusion rules for Visual Studio & CMake artifacts
+-- CMakeLists.txt                # Enterprise cross-platform compilation script
```

---

## Design Patterns & C++20 Implementations Showcase

### 1. Zero-Copy Semantics & Memory Safety
The engine heavily utilizes `std::string_view` across all interface parameters to eliminate unnecessary string copy allocations during high-frequency parsing. Smart pointers strictly define compile-time ownership, ensuring zero memory leaks without runtime garbage collection overhead.

### 2. Modern Multi-Threading (`std::jthread`)
The background engine utilizes the C++20 `std::jthread` paradigm, which solves the traditional thread leak problems by automatically signaling an internal `stop_token` and joining implicitly upon object destruction.

### 3. Isolated Automated Testing
Through structural dependency injection, the unit test engine completely simulates system interactions. The test suites validate how the `PlmClient` reacts to null pointers, empty data packets, and normal payloads without needing a live network connection to an enterprise server.

---

##  Compilation & Build Instructions

This project compiles natively across platforms using **CMake 3.20+** and a compiler supporting **C++20** (e.g., MSVC 2022, GCC 11+, Clang 13+).

### Command Line Build Pipeline
From the root directory of the repository, execute the following commands in your terminal:

```bash
# 1. Generate local build caching infrastructure targets
cmake -B build

# 2. Compile all production and testing binaries simultaneously
cmake --build build
```

### Running the Application Execution Paths
```bash
# Run the primary client application simulation
./build/client/plm_client   (or .\build\client\Debug\plm_client.exe on Windows)

# Run the automated unit test suite validation checks
ctest --test-dir build      (or run via Visual Studio Test Explorer)
```

#prompts used

#to create blueprint
"I am a C++ Tech Lead building a backend architectural blueprint for a PTC Windchill PLM client using C++20 and CMake. I value clean code, memory safety, dependency injection, modern standard libraries (std::string_view, smart pointers), and zero-copy performance. Please act as my senior staff engineer peer. Before we write any code, give me a quick high-level architectural overview of how we should structure an asynchronous, decoupled event loop to poll metadata from a REST endpoint."

#add core logic
"Now that we have established our core PlmClient structure, let's implement the actual network communication layer. Please generate a clean, modern C++20 header file (`include/core/WindchillRestConnector.hpp`) and an implementation file (`src/core/WindchillRestConnector.cpp`) that inherits from `IPlmConnector`. 

Assume we are using a lightweight, header-only HTTP library like `cpp-httplib` or mock native system sockets. It needs to:
1. Accept a base URL and an OAuth authentication token in its constructor.
2. Implement `fetchPartData(std::string_view partNumber)` to send an asynchronous GET request to '/Windchill/v1/ProdMgmt/Parts(partNumber)'.
3. Gracefully handle HTTP timeouts or 401 Unauthorized errors using standard C++ exceptions or an error-handling variant (`std::expected` or `std::optional`).

Keep the implementation thread-safe and decoupled, maintaining our Tech Lead design pattern approach."

#add multithreading
"I have a working synchronous PlmClient. I want to build a headless, multi-threaded task scheduler using C++20 std::jthread, std::mutex, and std::condition_variable. Generate a header file (AsyncPlmScheduler.hpp) that queues up multiple part-number requests and processes them concurrently using a pool of background threads without locking the execution runner."

IPLMConnector -
 * @brief Abstract interface defining the contract for PLM System Communications.
* Showcase-focus: Decoupling, Interface-Segregation, and Modern C++ Types.
 */


PlmEngine -
 /* @brief Orchestrator class managing PLM workflow operations.
 * Showcase-focus: Dependency Injection and Memory Management via Smart Pointers.
 */
