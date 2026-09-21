#pragma once

#include "llm/LLMInterface.h"

class MockLLM : public LLMInterface {
public:
    std::string sendPrompt(const std::string& prompt) override;
};
