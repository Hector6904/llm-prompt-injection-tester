#include "models/TestResult.h"

TestResult::TestResult(int resultId, int testId, int runId, const std::string& response,
                       const std::string& status, const std::string& severity,
                       const std::string& analysis, double executionTime,
                       const std::string& timestamp)
    : resultId_(resultId), testId_(testId), runId_(runId), response_(response),
      status_(status), severity_(severity), analysis_(analysis),
      executionTime_(executionTime), timestamp_(timestamp) {}

int TestResult::getResultId() const { return resultId_; }
int TestResult::getTestId() const { return testId_; }
int TestResult::getRunId() const { return runId_; }
const std::string& TestResult::getResponse() const { return response_; }
const std::string& TestResult::getStatus() const { return status_; }
const std::string& TestResult::getSeverity() const { return severity_; }
const std::string& TestResult::getAnalysis() const { return analysis_; }
double TestResult::getExecutionTime() const { return executionTime_; }
const std::string& TestResult::getTimestamp() const { return timestamp_; }

void TestResult::setResultId(int resultId) { resultId_ = resultId; }
void TestResult::setTestId(int testId) { testId_ = testId; }
void TestResult::setRunId(int runId) { runId_ = runId; }
void TestResult::setResponse(const std::string& response) { response_ = response; }
void TestResult::setStatus(const std::string& status) { status_ = status; }
void TestResult::setSeverity(const std::string& severity) { severity_ = severity; }
void TestResult::setAnalysis(const std::string& analysis) { analysis_ = analysis; }
void TestResult::setExecutionTime(double executionTime) { executionTime_ = executionTime; }
void TestResult::setTimestamp(const std::string& timestamp) { timestamp_ = timestamp; }
