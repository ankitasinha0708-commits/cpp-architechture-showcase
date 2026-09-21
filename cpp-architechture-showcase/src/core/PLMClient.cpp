#include "core/PlmClient.hpp"
#include <stdexcept>

namespace PlmEngine {

    PlmClient::PlmClient(std::unique_ptr<IPlmConnector> connector)
        : m_connector(std::move(connector)) {
        if (!m_connector) {
            throw std::invalid_argument("PLM Connector dependency cannot be null.");
        }
    }

    std::string PlmClient::getPartDetails(std::string_view partNumber) {
        if (partNumber.empty()) {
            return "{\"error\": \"Invalid Part Number Provided\"}";
        }

        // Delegate the network fetch mechanism entirely to the interface implementation
        return m_connector->fetchPartData(partNumber);
    }

} // namespace PlmEngine
