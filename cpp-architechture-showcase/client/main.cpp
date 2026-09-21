#include "core/PlmClient.hpp"
#include "core/AsyncPlmScheduler.hpp"
#include <iostream>
#include <chrono>

class WindchillSimulationConnector : public PlmEngine::IPlmConnector {
public:
    std::string fetchPartData(std::string_view partNumber) override {
        // Simulate a slight server network transmission delay latency
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        return "{\"wtpartNumber\": \"" + std::string(partNumber) + "\", \"status\": \"RELEASED\"}";
    }
};

int main() {
    std::cout << "=== Asynchronous PLM Execution Pipeline Initiated ===\n\n";

    try {
        auto mockConnector = std::make_unique<WindchillSimulationConnector>();
        auto plmClient = std::make_shared<PlmEngine::PlmClient>(std::move(mockConnector));

        // Initialize background thread manager layer
        PlmEngine::AsyncPlmScheduler scheduler(plmClient);

        // Queue requests smoothly without pausing execution paths
        std::cout << "[Main Thread] Queueing 3 part requests...\n";
        scheduler.queuePartRequest("999-0001-A");
        scheduler.queuePartRequest("999-0002-B");
        scheduler.queuePartRequest("999-0003-C");

        std::cout << "[Main Thread] Requests queued. Performing independent execution logic...\n";
        for (int i = 1; i <= 3; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << "[Main Thread] Running background calculation task tick: " << i << "\n";
        }

        std::cout << "\n[Main Thread] Completed calculations. Wrapping up application execution context...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(600)); // Buffer to ensure background outputs complete before exit
    }
    catch (const std::exception& ex) {
        std::cerr << "Critical runtime issue: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
