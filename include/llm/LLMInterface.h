#pragma once

#include <string>

class LLMInterface {
public:
    virtual ~LLMInterface() = default;

    virtual std::string sendPrompt(const std::string& prompt) = 0;
};
