#include "core/PlmClient.hpp"
#include <iostream>

// Concrete simulation class to mimic real PTC Windchill server responses
class WindchillSimulationConnector : public PlmEngine::IPlmConnector {
public:
    std::string fetchPartData(std::string_view partNumber) override {
        // Simulating a structured JSON payload returned by a Windchill REST API
        return "{\n"
            "  \"wtpartNumber\": \"" + std::string(partNumber) + "\",\n"
            "  \"name\": \"Assembly Component\",\n"
            "  \"version\": \"A.1\",\n"
            "  \"lifecycleState\": \"INWORK\"\n"
            "}";
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "   PTC Windchill C++ Backend Architecture Showcase   \n";
    std::cout << "====================================================\n\n";

    try {
        // Instantiate the simulated connector payload
        auto mockConnector = std::make_unique<WindchillSimulationConnector>();

        // Inject the dependency safely into the core client orchestrator
        PlmEngine::PlmClient plmClient(std::move(mockConnector));

        // Execute processing pipeline
        std::string partData = plmClient.getPartDetails("0000004512");

        std::cout << "Server Response Payload:\n" << partData << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Execution Pipeline Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
