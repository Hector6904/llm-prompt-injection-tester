#include <iostream>

#include "llm/LLMInterface.h"
#include "llm/MockLLM.h"
#include "tests/InstructionOverrideTest.h"

int main() {
    MockLLM mockLlm;
    LLMInterface& llm = mockLlm;
    InstructionOverrideTest test(llm);

    const std::string response = test.execute();

    std::cout << "LLM Prompt Injection Vulnerability Tester\n";
    std::cout << "Flow: InstructionOverrideTest -> LLMInterface -> MockLLM -> response\n";
    std::cout << "Test name: " << test.getTestName() << '\n';
    std::cout << "Category: " << test.getCategory() << '\n';
    std::cout << "Prompt: " << test.getPrompt() << '\n';
    std::cout << "Response: " << response << '\n';

    return 0;
}
