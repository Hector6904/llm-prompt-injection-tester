#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <memory>
#include <string>

#include <cppconn/connection.h>

class DatabaseManager {
public:
    DatabaseManager();
    bool connect();
    bool createTestRun(int modelId);
    bool createTestResult(
        int runId,
        int testId,
        const std::string& response,
        const std::string& status,
        const std::string& severity,
        const std::string& analysis,
        double executionTime
    );

private:
    std::string host_;
    std::string username_;
    std::string password_;
    std::string database_;

    std::unique_ptr<sql::Connection> connection_;
};

#endif