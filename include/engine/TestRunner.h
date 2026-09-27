#pragma once

#include "models/TestResult.h"

class InjectionTest;
class ResponseAnalyzer;

class TestRunner {
public:
    explicit TestRunner(ResponseAnalyzer& analyzer);

    TestResult runTest(InjectionTest& test, int runId) const;

private:
    ResponseAnalyzer& analyzer_;
};
