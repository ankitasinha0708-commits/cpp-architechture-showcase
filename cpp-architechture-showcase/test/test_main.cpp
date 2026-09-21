#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/PlmClient.hpp"
#include "core/IPlmConnector.hpp"
#include <stdexcept>

// 1. Create a Mock class for the PLM Connector Interface
class MockPlmConnector : public PlmEngine::IPlmConnector {
public:
    // MOCK_METHOD overrides the virtual function for testing assertions
    MOCK_METHOD(std::string, fetchPartData, (std::string_view partNumber), (override));
};

// 2. Test Suite for checking initialization constraints
TEST(PlmClientTest, InitializationThrowsOnNullDependency) {
    // Assert that passing a nullptr constructor argument throws an exception
    EXPECT_THROW({
        PlmEngine::PlmClient client(nullptr);
        }, std::invalid_argument);
}

// 3. Test Suite for checking validation workflows
TEST(PlmClientTest, GetPartDetailsReturnsErrorOnEmptyInput) {
    auto mockConnector = std::make_unique<MockPlmConnector>();
    PlmEngine::PlmClient client(std::move(mockConnector));

    std::string result = client.getPartDetails("");
    EXPECT_TRUE(result.find("error") != std::string::npos);
}

// 4. Test Suite for verifying core interface routing mechanics
TEST(PlmClientTest, GetPartDetailsRoutesCallToConnectorSuccessfully) {
    auto mockConnector = std::make_unique<MockPlmConnector>();

    // Set expectations: fetchPartData should be called exactly once with "001" 
    // and must return our designated simulated string payload.
    EXPECT_CALL(*mockConnector, fetchPartData(std::string_view("001")))
        .Times(1)
        .WillOnce(::testing::Return("{\"wtpartNumber\": \"001\", \"status\": \"TEST\"}"));

    PlmEngine::PlmClient client(std::move(mockConnector));
    std::string result = client.getPartDetails("001");

    EXPECT_EQ(result, "{\"wtpartNumber\": \"001\", \"status\": \"TEST\"}");
}

// The gtest_main library handles the actual main() entry initialization automatically
