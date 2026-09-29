#include "engine/TestExecutionCoordinator.h"

#include <climits>
#include <utility>

#include "data_structures/Search.h"
#include "data_structures/Sort.h"
#include "engine/TestRunner.h"
#include "models/InjectionTest.h"

TestExecutionCoordinator::TestExecutionCoordinator(TestRunner& runner)
    : runner_(runner), pendingTests_{}, resultStack_{}, nextResultId_(1000),
      resultsById_{}, executedTestIds_{}, invalidTestIds_{}, createdResultIds_{},
      stackOverflowCount_(0U) {
    queue_init(&pendingTests_);
    stack_init(&resultStack_);
}

bool TestExecutionCoordinator::enqueueTestId(int testId) {
    return queue_enqueue(&pendingTests_, testId);
}

void TestExecutionCoordinator::executePendingTests(const TestRegistry& tests, int runId) {
    int testId = 0;

    while (queue_dequeue(&pendingTests_, &testId)) {
        const auto foundTest = tests.find(testId);
        if (foundTest == tests.end() || foundTest->second == nullptr) {
            invalidTestIds_.push_back(testId);
            continue;
        }

        TestResult result = runner_.runTest(*foundTest->second, runId);
        const int resultId = nextResultId();
        result.setResultId(resultId);
        resultsById_.emplace(resultId, std::move(result));
        executedTestIds_.push_back(testId);
        createdResultIds_.push_back(resultId);

        if (!stack_push(&resultStack_, resultId)) {
            ++stackOverflowCount_;
        }
    }
}

const std::vector<int>& TestExecutionCoordinator::getExecutedTestIds() const {
    return executedTestIds_;
}

const std::vector<int>& TestExecutionCoordinator::getInvalidTestIds() const {
    return invalidTestIds_;
}

const std::vector<int>& TestExecutionCoordinator::getCreatedResultIds() const {
    return createdResultIds_;
}

std::size_t TestExecutionCoordinator::getStoredStackResultCount() const {
    return resultStack_.top;
}

std::size_t TestExecutionCoordinator::getStackOverflowCount() const {
    return stackOverflowCount_;
}

const TestResult* TestExecutionCoordinator::findResult(int resultId) const {
    const auto result = resultsById_.find(resultId);
    return result == resultsById_.end() ? nullptr : &result->second;
}

bool TestExecutionCoordinator::popLatestResultId(int* resultId) {
    return stack_pop(&resultStack_, resultId);
}

int TestExecutionCoordinator::findResultIdLinear(int resultId) const {
    if (createdResultIds_.empty()) {
        return -1;
    }

    return linear_search(createdResultIds_.data(), createdResultIds_.size(), resultId);
}

bool TestExecutionCoordinator::sortResultIds(
    ResultIdSortAlgorithm algorithm, std::vector<int>* sortedResultIds) const {
    if (sortedResultIds == nullptr) {
        return false;
    }

    *sortedResultIds = createdResultIds_;
    if (sortedResultIds->empty()) {
        return true;
    }

    int* values = sortedResultIds->data();
    const std::size_t size = sortedResultIds->size();

    switch (algorithm) {
        case ResultIdSortAlgorithm::Bubble:
            return bubble_sort(values, size);
        case ResultIdSortAlgorithm::Selection:
            return selection_sort(values, size);
        case ResultIdSortAlgorithm::Insertion:
            return insertion_sort(values, size);
        case ResultIdSortAlgorithm::Merge:
            return merge_sort(values, size);
        case ResultIdSortAlgorithm::Quick:
            return quick_sort(values, size);
    }

    return false;
}

int TestExecutionCoordinator::findResultIdBinary(
    const std::vector<int>& sortedResultIds, int resultId) const {
    if (sortedResultIds.empty()) {
        return -1;
    }

    return binary_search(sortedResultIds.data(), sortedResultIds.size(), resultId);
}

int TestExecutionCoordinator::nextResultId() {
    const int resultId = nextResultId_;
    if (nextResultId_ >= INT_MIN + 10) {
        nextResultId_ -= 10;
    } else {
        nextResultId_ = INT_MAX;
        while (resultsById_.find(nextResultId_) != resultsById_.end() &&
               nextResultId_ > INT_MIN) {
            --nextResultId_;
        }
    }
    return resultId;
}
