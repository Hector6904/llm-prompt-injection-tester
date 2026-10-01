#include "models/TestRun.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

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

TestRun::TestRun(int runId, int modelId)
    : TestRun(runId, modelId, currentTimestamp(), "", 0) {}

TestRun::TestRun(int runId, int modelId, const std::string& startedAt,
                 const std::string& completedAt, int totalTests)
    : runId_(runId), modelId_(modelId), startedAt_(startedAt),
      completedAt_(completedAt), totalTests_(totalTests) {}

int TestRun::getRunId() const { return runId_; }
int TestRun::getModelId() const { return modelId_; }
const std::string& TestRun::getStartedAt() const { return startedAt_; }
const std::string& TestRun::getCompletedAt() const { return completedAt_; }
int TestRun::getTotalTests() const { return totalTests_; }

void TestRun::setRunId(int runId) { runId_ = runId; }
void TestRun::setModelId(int modelId) { modelId_ = modelId; }
void TestRun::setStartedAt(const std::string& startedAt) { startedAt_ = startedAt; }
void TestRun::setCompletedAt(const std::string& completedAt) { completedAt_ = completedAt; }
void TestRun::setTotalTests(int totalTests) { totalTests_ = totalTests; }

bool TestRun::complete(int totalTests) {
    if (isCompleted()) {
        return false;
    }

    totalTests_ = totalTests;
    completedAt_ = currentTimestamp();
    return true;
}

bool TestRun::isCompleted() const { return !completedAt_.empty(); }
