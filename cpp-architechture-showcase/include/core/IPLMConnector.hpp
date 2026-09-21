#pragma once
#include <string>
#include <string_view>

namespace PlmEngine {

    
    class IPlmConnector {
    public:
        virtual ~IPlmConnector() = default;

        // [[nodiscard]] forces the caller to handle the returned string data
        // std::string_view avoids expensive string copy allocations
        [[nodiscard]] virtual std::string fetchPartData(std::string_view partNumber) = 0;
    };

} // namespace PlmEngine
