#pragma once

#include "models/InjectionTest.h"

class LLMInterface;

class InstructionOverrideTest : public InjectionTest {
public:
    explicit InstructionOverrideTest(LLMInterface& llm, int testId = 1);

    std::string execute() override;

private:
    LLMInterface& llm_;
};
