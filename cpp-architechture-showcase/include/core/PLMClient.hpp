#pragma once
#include "IPlmConnector.hpp"
#include <memory>

namespace PlmEngine {

    
    class PlmClient {
    private:
        std::unique_ptr<IPlmConnector> m_connector;

    public:
        // Explicit constructor prevents accidental implicit type conversions
        explicit PlmClient(std::unique_ptr<IPlmConnector> connector);

        [[nodiscard]] std::string getPartDetails(std::string_view partNumber);
    };

} // namespace PlmEngine

