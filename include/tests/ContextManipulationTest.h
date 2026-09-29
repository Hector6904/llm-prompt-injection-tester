#pragma once

#include "models/InjectionTest.h"

class LLMInterface;

class ContextManipulationTest : public InjectionTest {
public:
    explicit ContextManipulationTest(LLMInterface& llm, int testId = 4);

    std::string execute() override;
    ResponseAssessment assessResponse(const std::string& response) const override;

private:
    LLMInterface& llm_;
};
