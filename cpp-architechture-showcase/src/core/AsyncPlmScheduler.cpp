#include "core/AsyncPlmScheduler.hpp"
#include <iostream>

namespace PlmEngine {

    AsyncPlmScheduler::AsyncPlmScheduler(std::shared_ptr<PlmClient> plmClient)
        : m_plmClient(std::move(plmClient)) {

        if (!m_plmClient) {
            throw std::invalid_argument("PlmClient target pointer cannot be null.");
        }

        // Launch background thread passing the cooperative C++20 stop token
        m_workerThread = std::jthread([this](std::stop_token token) {
            workerLoop(token);
            });
    }

    AsyncPlmScheduler::~AsyncPlmScheduler() {
        // std::jthread handles internal signal request stops and joins automatically on destruction!
    }

    void AsyncPlmScheduler::queuePartRequest(std::string_view partNumber) {
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_taskQueue.push(std::string(partNumber));
        }
        m_cv.notify_one(); // Wake up worker thread
    }

    void AsyncPlmScheduler::workerLoop(std::stop_token stopToken) {
        while (!stopToken.stop_requested()) {
            std::string partNumber;

            {
                std::unique_lock<std::mutex> lock(m_queueMutex);

                // Wait until a task arrives OR a stop request is issued to prevent resource deadlocks
                m_cv.wait(lock, stopToken, [this]() {
                    return !m_taskQueue.empty();
                    });

                if (stopToken.stop_requested() && m_taskQueue.empty()) {
                    return;
                }

                partNumber = std::move(m_taskQueue.front());
                m_taskQueue.pop();
            }

            // Execute processing outside the lock scope so queueing remains unblocked
            try {
                std::string result = m_plmClient->getPartDetails(partNumber);

                // Simulating logging output processing
                std::cout << "[Background Worker Thread " << std::this_thread::get_id()
                    << "] Successfully processed Part: " << partNumber << "\n"
                    << "Data: " << result << "\n\n";
            }
            catch (const std::exception& ex) {
                std::cerr << "[Background Worker Error] Failed processing " << partNumber
                    << " -> " << ex.what() << "\n";
            }
        }
    }

} // namespace PlmEngine
