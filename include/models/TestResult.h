#pragma once

#include <string>

class TestResult {
public:
    TestResult(int resultId, int testId, int runId, const std::string& response,
               const std::string& status, const std::string& severity,
               const std::string& analysis, double executionTime,
               const std::string& timestamp);

    int getResultId() const;
    int getTestId() const;
    int getRunId() const;
    const std::string& getResponse() const;
    const std::string& getStatus() const;
    const std::string& getSeverity() const;
    const std::string& getAnalysis() const;
    double getExecutionTime() const;
    const std::string& getTimestamp() const;

    void setResultId(int resultId);
    void setTestId(int testId);
    void setRunId(int runId);
    void setResponse(const std::string& response);
    void setStatus(const std::string& status);
    void setSeverity(const std::string& severity);
    void setAnalysis(const std::string& analysis);
    void setExecutionTime(double executionTime);
    void setTimestamp(const std::string& timestamp);

private:
    int resultId_;
    int testId_;
    int runId_;
    std::string response_;
    std::string status_;
    std::string severity_;
    std::string analysis_;
    double executionTime_;
    std::string timestamp_;
};
