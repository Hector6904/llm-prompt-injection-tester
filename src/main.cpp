#include <iostream>
#include <unordered_map>
#include <vector>

#include "analysis/ResponseAnalyzer.h"
#include "engine/TestExecutionCoordinator.h"
#include "engine/TestRunner.h"
#include "llm/LLMInterface.h"
#include "llm/MockLLM.h"
#include "tests/InstructionOverrideTest.h"

namespace {

void displayResult(const TestResult& result) {
    std::cout << "Result ID: " << result.getResultId() << '\n';
    std::cout << "Test ID: " << result.getTestId() << '\n';
    std::cout << "Status: " << result.getStatus() << '\n';
    std::cout << "Severity: " << result.getSeverity() << '\n';
    std::cout << "Analysis: " << result.getAnalysis() << '\n';
    std::cout << "Execution time: " << result.getExecutionTime() << " ms\n";
}

void displayIds(const std::vector<int>& ids) {
    for (const int id : ids) {
        std::cout << ' ' << id;
    }
    std::cout << '\n';
}

}  // namespace

int main() {
    MockLLM mockLlm;
    LLMInterface& llm = mockLlm;
    ResponseAnalyzer analyzer;
    TestRunner runner(analyzer);
    InstructionOverrideTest firstTest(llm, 30);
    InstructionOverrideTest secondTest(llm, 10);
    InstructionOverrideTest thirdTest(llm, 20);

    TestExecutionCoordinator coordinator(runner);
    const TestExecutionCoordinator::TestRegistry tests = {
        {firstTest.getTestId(), &firstTest},
        {secondTest.getTestId(), &secondTest},
        {thirdTest.getTestId(), &thirdTest},
    };

    std::cout << "LLM Prompt Injection Vulnerability Tester\n";
    std::cout << "Flow: C queue -> TestRunner -> MockLLM -> ResponseAnalyzer -> "
                 "C stack/search/sort\n";

    for (const int testId : {30, 10, 20, 999}) {
        if (!coordinator.enqueueTestId(testId)) {
            std::cerr << "Could not enqueue test ID " << testId << ".\n";
        }
    }
    coordinator.executePendingTests(tests, 1);

    std::cout << "FIFO executed test IDs:";
    displayIds(coordinator.getExecutedTestIds());
    for (const int invalidTestId : coordinator.getInvalidTestIds()) {
        std::cout << "Skipped unresolved test ID: " << invalidTestId << '\n';
    }

    std::cout << "Created result IDs (execution order):";
    displayIds(coordinator.getCreatedResultIds());

    const int resultIdToFind = coordinator.getCreatedResultIds().front();
    std::cout << "Linear search for result ID " << resultIdToFind << ": index "
              << coordinator.findResultIdLinear(resultIdToFind) << '\n';
    std::cout << "Linear search for missing result ID 9999: index "
              << coordinator.findResultIdLinear(9999) << '\n';

    std::vector<int> sortedResultIds;
    if (!coordinator.sortResultIds(ResultIdSortAlgorithm::Quick, &sortedResultIds)) {
        std::cerr << "Could not sort result IDs.\n";
        return 1;
    }

    std::cout << "Quick-sorted result IDs:";
    displayIds(sortedResultIds);
    std::cout << "Binary search for result ID " << resultIdToFind << ": index "
              << coordinator.findResultIdBinary(sortedResultIds, resultIdToFind) << '\n';

    std::cout << "Results retrieved through their sorted IDs:\n";
    for (const int resultId : sortedResultIds) {
        const TestResult* result = coordinator.findResult(resultId);
        if (result != nullptr) {
            displayResult(*result);
        }
    }

    std::cout << "LIFO result IDs popped from the C stack:";
    int stackedResultId = 0;
    while (coordinator.popLatestResultId(&stackedResultId)) {
        std::cout << ' ' << stackedResultId;
    }
    std::cout << '\n';

    return 0;
}
