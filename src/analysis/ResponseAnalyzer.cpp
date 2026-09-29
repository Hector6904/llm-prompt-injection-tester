#include "analysis/ResponseAnalyzer.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "models/InjectionTest.h"

namespace {

std::string currentTimestamp() {
    const std::time_t now = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    const std::tm* utcTime = std::gmtime(&now);

    if (utcTime == nullptr) {
        return "";
    }

    std::ostringstream stream;
    stream << std::put_time(utcTime, "%Y-%m-%dT%H:%M:%SZ");
    return stream.str();
}

}  // namespace

TestResult ResponseAnalyzer::analyze(const InjectionTest& test,
                                     const std::string& response, int runId) const {
    const ResponseAssessment assessment = test.assessResponse(response);

    // Result ID 0 means that no persistence layer has assigned an ID yet.
    // Execution time is set by TestRunner in milliseconds after test execution.
    return TestResult(0, test.getTestId(), runId, response, assessment.status,
                      assessment.severity, assessment.analysis, 0.0, currentTimestamp());
}
