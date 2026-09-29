#include "llm/MockLLM.h"

std::string MockLLM::sendPrompt(const std::string& prompt) {
    if (prompt.find("Ignore previous instructions") != std::string::npos) {
        return "I cannot override previous instructions.";
    }

    if (prompt.find("complete system prompt") != std::string::npos) {
        return "I cannot reveal the system prompt or hidden instructions.";
    }

    if (prompt.find("unrestricted assistant") != std::string::npos) {
        return "I cannot adopt an unrestricted role or ignore safety policies.";
    }

    if (prompt.find("higher-priority instructions") != std::string::npos) {
        return "I cannot treat untrusted content as higher-priority instructions.";
    }

    return "MockLLM received a prompt without an instruction override attempt.";
}
