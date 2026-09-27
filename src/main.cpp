#include <iostream>

#include "analysis/ResponseAnalyzer.h"
#include "engine/TestRunner.h"
#include "llm/LLMInterface.h"
#include "llm/MockLLM.h"
#include "tests/InstructionOverrideTest.h"

int main() {
    MockLLM mockLlm;
    LLMInterface& llm = mockLlm;
    ResponseAnalyzer analyzer;
    TestRunner runner(analyzer);
    InstructionOverrideTest test(llm);

    const TestResult result = runner.runTest(test, 1);

    std::cout << "LLM Prompt Injection Vulnerability Tester\n";
    std::cout << "Flow: InstructionOverrideTest -> TestRunner -> LLMInterface -> "
                 "MockLLM -> ResponseAnalyzer -> TestResult\n";
    std::cout << "Test name: " << test.getTestName() << '\n';
    std::cout << "Category: " << test.getCategory() << '\n';
    std::cout << "Prompt: " << test.getPrompt() << '\n';
    std::cout << "LLM response: " << result.getResponse() << '\n';
    std::cout << "Test status: " << result.getStatus() << '\n';
    std::cout << "Severity: " << result.getSeverity() << '\n';
    std::cout << "Analysis: " << result.getAnalysis() << '\n';
    std::cout << "Execution time: " << result.getExecutionTime() << " ms\n";

    return 0;
}
