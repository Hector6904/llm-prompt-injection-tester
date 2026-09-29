#pragma once

#include "models/InjectionTest.h"

class LLMInterface;

class PromptExtractionTest : public InjectionTest {
public:
    explicit PromptExtractionTest(LLMInterface& llm, int testId = 2);

    std::string execute() override;
    ResponseAssessment assessResponse(const std::string& response) const override;

private:
    LLMInterface& llm_;
};
