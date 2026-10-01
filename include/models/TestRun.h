#pragma once

#include <string>

class TestRun {
public:
    TestRun(int runId, int modelId);
    TestRun(int runId, int modelId, const std::string& startedAt,
            const std::string& completedAt, int totalTests);

    int getRunId() const;
    int getModelId() const;
    const std::string& getStartedAt() const;
    const std::string& getCompletedAt() const;
    int getTotalTests() const;

    void setRunId(int runId);
    void setModelId(int modelId);
    void setStartedAt(const std::string& startedAt);
    void setCompletedAt(const std::string& completedAt);
    void setTotalTests(int totalTests);

    /* Returns false without changing the run when it is already complete. */
    bool complete(int totalTests);
    bool isCompleted() const;

private:
    int runId_;
    int modelId_;
    std::string startedAt_;
    std::string completedAt_;
    int totalTests_;
};
