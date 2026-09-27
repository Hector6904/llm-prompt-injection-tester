#pragma once

#include <string>

#include "models/TestResult.h"

class InjectionTest;

class ResponseAnalyzer {
public:
    TestResult analyze(const InjectionTest& test, const std::string& response,
                       int runId) const;
};
