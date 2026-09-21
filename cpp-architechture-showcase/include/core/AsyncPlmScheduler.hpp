#pragma once
#include "PlmClient.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <functional>

namespace PlmEngine {

    /**
     * @brief Manages asynchronous background processing of PLM Part Requests.
     * Showcase-focus: C++20 std::jthread, Thread-Safety, and Producer-Consumer Pattern.
     */
    class AsyncPlmScheduler {
    private:
        std::shared_ptr<PlmClient> m_plmClient;
        std::queue<std::string> m_taskQueue;
        std::mutex m_queueMutex;
        std::condition_variable_any m_cv;
        std::jthread m_workerThread; // C++20 automatically joining thread

        // Background worker loop execution loop
        void workerLoop(std::stop_token stopToken);

    public:
        explicit AsyncPlmScheduler(std::shared_ptr<PlmClient> plmClient);
        ~AsyncPlmScheduler();

        // Prevent copying to maintain strict ownership rules
        AsyncPlmScheduler(const AsyncPlmScheduler&) = delete;
        AsyncPlmScheduler& operator=(const AsyncPlmScheduler&) = delete;

        // Push a request safely from any thread
        void queuePartRequest(std::string_view partNumber);
    };

} // namespace PlmEngine
