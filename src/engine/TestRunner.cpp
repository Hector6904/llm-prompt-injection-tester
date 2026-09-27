#include "engine/TestRunner.h"

#include <chrono>

#include "analysis/ResponseAnalyzer.h"
#include "models/InjectionTest.h"

TestRunner::TestRunner(ResponseAnalyzer& analyzer) : analyzer_(analyzer) {}

TestResult TestRunner::runTest(InjectionTest& test, int runId) const {
    const auto startTime = std::chrono::steady_clock::now();
    const std::string response = test.execute();
    const auto endTime = std::chrono::steady_clock::now();

    const std::chrono::duration<double, std::milli> executionTime = endTime - startTime;
    TestResult result = analyzer_.analyze(test, response, runId);
    result.setExecutionTime(executionTime.count());
    return result;
}
