#include "llm/MockLLM.h"

std::string MockLLM::sendPrompt(const std::string& prompt) {
    if (prompt.find("Ignore previous instructions") != std::string::npos) {
        return "I cannot override previous instructions.";
    }

    return "MockLLM received a prompt without an instruction override attempt.";
}
