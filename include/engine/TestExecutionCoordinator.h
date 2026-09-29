#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

#include "data_structures/Queue.h"
#include "data_structures/Stack.h"
#include "models/TestResult.h"

class InjectionTest;
class TestRunner;

enum class ResultIdSortAlgorithm {
    Bubble,
    Selection,
    Insertion,
    Merge,
    Quick
};

/*
 * Connects the integer-only C modules to the C++ test engine. The registry owns
 * neither tests nor TestRunner; callers must keep them alive while processing.
 */
class TestExecutionCoordinator {
public:
    using TestRegistry = std::unordered_map<int, InjectionTest*>;

    explicit TestExecutionCoordinator(TestRunner& runner);

    bool enqueueTestId(int testId);
    void executePendingTests(const TestRegistry& tests, int runId);

    const std::vector<int>& getExecutedTestIds() const;
    const std::vector<int>& getInvalidTestIds() const;
    const std::vector<int>& getCreatedResultIds() const;
    std::size_t getStoredStackResultCount() const;
    std::size_t getStackOverflowCount() const;

    const TestResult* findResult(int resultId) const;
    bool popLatestResultId(int* resultId);

    int findResultIdLinear(int resultId) const;
    bool sortResultIds(ResultIdSortAlgorithm algorithm,
                       std::vector<int>* sortedResultIds) const;
    int findResultIdBinary(const std::vector<int>& sortedResultIds,
                           int resultId) const;

private:
    int nextResultId();

    TestRunner& runner_;
    TestQueue pendingTests_;
    TestResultStack resultStack_;
    int nextResultId_;
    std::unordered_map<int, TestResult> resultsById_;
    std::vector<int> executedTestIds_;
    std::vector<int> invalidTestIds_;
    std::vector<int> createdResultIds_;
    std::size_t stackOverflowCount_;
};
