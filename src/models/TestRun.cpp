#include "models/TestRun.h"

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
