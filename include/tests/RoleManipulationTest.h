#pragma once

#include "models/InjectionTest.h"

class LLMInterface;

class RoleManipulationTest : public InjectionTest {
public:
    explicit RoleManipulationTest(LLMInterface& llm, int testId = 3);

    std::string execute() override;
    ResponseAssessment assessResponse(const std::string& response) const override;

private:
    LLMInterface& llm_;
};
