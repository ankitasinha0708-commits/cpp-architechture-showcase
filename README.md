# cpp-architechture-showcase
Small project to showcase Cpp architechtures


#prompts used

"I am a C++ Tech Lead building a backend architectural blueprint for a PTC Windchill PLM client using C++20 and CMake. I value clean code, memory safety, dependency injection, modern standard libraries (std::string_view, smart pointers), and zero-copy performance. Please act as my senior staff engineer peer. Before we write any code, give me a quick high-level architectural overview of how we should structure an asynchronous, decoupled event loop to poll metadata from a REST endpoint."

"Now that we have established our core PlmClient structure, let's implement the actual network communication layer. Please generate a clean, modern C++20 header file (`include/core/WindchillRestConnector.hpp`) and an implementation file (`src/core/WindchillRestConnector.cpp`) that inherits from `IPlmConnector`. 

Assume we are using a lightweight, header-only HTTP library like `cpp-httplib` or mock native system sockets. It needs to:
1. Accept a base URL and an OAuth authentication token in its constructor.
2. Implement `fetchPartData(std::string_view partNumber)` to send an asynchronous GET request to '/Windchill/v1/ProdMgmt/Parts(partNumber)'.
3. Gracefully handle HTTP timeouts or 401 Unauthorized errors using standard C++ exceptions or an error-handling variant (`std::expected` or `std::optional`).

Keep the implementation thread-safe and decoupled, maintaining our Tech Lead design pattern approach."


IPLMConnector -
 * @brief Abstract interface defining the contract for PLM System Communications.
* Showcase-focus: Decoupling, Interface-Segregation, and Modern C++ Types.
 */


PlmEngine -
 /* @brief Orchestrator class managing PLM workflow operations.
 * Showcase-focus: Dependency Injection and Memory Management via Smart Pointers.
 */
