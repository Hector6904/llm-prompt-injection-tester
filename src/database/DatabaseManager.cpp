#include "database/DatabaseManager.h"

#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>

DatabaseManager::DatabaseManager()
    : host_("localhost"),
    username_("root"),
    password_("Ira@sql"),
    database_("llm_injection_tester") {
}

bool DatabaseManager::connect() {
    try {
        sql::mysql::MySQL_Driver* driver =
            sql::mysql::get_mysql_driver_instance();


        if (driver == nullptr)
        {
            std::cout << "Driver is NULL\n";
            return false;
        }

        std::cout << "Driver loaded successfully\n";


        std::cout << "Host = " << host_ << '\n';
        std::cout << "User = " << username_ << '\n';
        std::cout << "Database = " << database_ << '\n';
        std::cout << "Password length = " << password_.length() << '\n';


        connection_.reset(
            driver->connect(host_, username_, password_));

        connection_->setSchema(database_);

        std::cout << "Database connection successful.\n";

        return true;
    }
    catch (const sql::SQLException& error) {
        std::cerr << "Database connection failed.\n";
        std::cerr << error.what() << '\n';

        return false;
    }
}

bool DatabaseManager::createTestRun(int modelId) {
    try {
        std::unique_ptr<sql::PreparedStatement> statement(
            connection_->prepareStatement(
                "INSERT INTO TEST_RUNS "
                "(model_id, started_at, total_tests) "
                "VALUES (?, NOW(), 0)"
            )
        );

        statement->setInt(1, modelId);

        statement->execute();

        std::cout << "Test run inserted into database.\n";

        return true;
    }
    catch (const sql::SQLException& error) {
        std::cerr << "Failed to insert test run.\n";
        std::cerr << error.what() << '\n';

        return false;
    }
}