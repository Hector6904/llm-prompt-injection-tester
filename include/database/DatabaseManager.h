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

private:
    std::string host_;
    std::string username_;
    std::string password_;
    std::string database_;

    std::unique_ptr<sql::Connection> connection_;
};

#endif